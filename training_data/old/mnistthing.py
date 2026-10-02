import os
import struct
from PIL import Image


# ============================================================
# FILES
# ============================================================

MNIST_IMAGES_FILE = "train-images.idx3-ubyte"
MNIST_LABELS_FILE = "train-labels.idx1-ubyte"

OUTPUT_FOLDER = "mnist_converted"

IMAGES_PER_FILE = 100

OUTPUT_WIDTH = 24
OUTPUT_HEIGHT = 36

# Every pixel greater than this becomes 1.
# 0 means every non-black pixel becomes 1.
THRESHOLD = 127


# ============================================================
# a, b, c, ... z, aa, ab, ...
# ============================================================

def batch_name(number):

    name = ""

    while True:

        number, remainder = divmod(number, 26)

        name = chr(ord('a') + remainder) + name

        if number == 0:
            break

        number -= 1

    return name


# ============================================================
# READ MNIST IMAGES
# ============================================================

def read_images(filename):

    with open(filename, "rb") as file:

        magic_number = struct.unpack(">I", file.read(4))[0]

        if magic_number != 2051:
            raise ValueError(
                "Invalid MNIST image file."
            )

        number_of_images = struct.unpack(">I", file.read(4))[0]

        rows = struct.unpack(">I", file.read(4))[0]

        columns = struct.unpack(">I", file.read(4))[0]

        print("MNIST image count:", number_of_images)
        print("MNIST image size:", rows, "x", columns)

        if rows != 28 or columns != 28:
            raise ValueError(
                "MNIST images are expected to be 28x28."
            )

        images = []

        for i in range(number_of_images):

            image = file.read(28 * 28)

            if len(image) != 28 * 28:
                raise ValueError(
                    "Unexpected end of image file."
                )

            images.append(image)

    return images


# ============================================================
# READ MNIST LABELS
# ============================================================

def read_labels(filename):

    with open(filename, "rb") as file:

        magic_number = struct.unpack(">I", file.read(4))[0]

        if magic_number != 2049:
            raise ValueError(
                "Invalid MNIST label file."
            )

        number_of_labels = struct.unpack(">I", file.read(4))[0]

        labels = file.read(number_of_labels)

        if len(labels) != number_of_labels:
            raise ValueError(
                "Unexpected end of label file."
            )

    return labels


# ============================================================
# CONVERT 28x28 INTO 24x36 BINARY IMAGE
# ============================================================

def convert_image(mnist_pixels):

    image = Image.frombytes(
        "L",
        (28, 28),
        mnist_pixels
    )

    # Resize from 28x28 to 24x36
    image = image.resize(
        (OUTPUT_WIDTH, OUTPUT_HEIGHT),
        Image.Resampling.LANCZOS
    )

    pixels = list(image.getdata())

    rows = []

    for y in range(OUTPUT_HEIGHT):

        row = ""

        for x in range(OUTPUT_WIDTH):

            pixel = pixels[
                y * OUTPUT_WIDTH + x
            ]

            if pixel > THRESHOLD:
                row += "1"
            else:
                row += "0"

        rows.append(row)

    return rows


# ============================================================
# WRITE 100 IMAGES INTO ONE FILE
# ============================================================

def write_image_file(filename, images):

    with open(filename, "w") as file:

        for image_number, image in enumerate(images):

            file.write("start_draw_0:\n")

            rows = convert_image(image)

            for row_number, row in enumerate(rows):

                if image_number == len(images) - 1 and row_number == len(rows) - 1:
                    file.write(row)
                else:
                    file.write(row + "\n")


# ============================================================
# MAIN
# ============================================================

def main():

    print("Reading MNIST...")

    images = read_images(MNIST_IMAGES_FILE)

    labels = read_labels(MNIST_LABELS_FILE)

    print("Images:", len(images))
    print("Labels:", len(labels))

    if len(images) != len(labels):

        raise ValueError(
            "Number of images and labels do not match."
        )


    # ========================================================
    # SORT IMAGES BY DIGIT
    # ========================================================

    images_by_digit = [[] for _ in range(10)]

    for image, label in zip(images, labels):

        images_by_digit[label].append(image)


    # ========================================================
    # SHOW HOW MANY OF EACH DIGIT WE HAVE
    # ========================================================

    print()

    for digit in range(10):

        print(
            "Digit",
            digit,
            ":",
            len(images_by_digit[digit])
        )


    # ========================================================
    # FIND HOW MANY COMPLETE 100-IMAGE SETS WE CAN MAKE
    # ========================================================

    smallest_amount = min(
        len(images_by_digit[digit])
        for digit in range(10)
    )

    number_of_sets = smallest_amount // IMAGES_PER_FILE

    print()
    print(
        "Complete sets:",
        number_of_sets
    )


    # ========================================================
    # CREATE OUTPUT DIRECTORY
    # ========================================================

    os.makedirs(
        OUTPUT_FOLDER,
        exist_ok=True
    )


    # ========================================================
    # CREATE SETS
    # ========================================================

    for set_number in range(number_of_sets):

        current_set_name = batch_name(set_number)

        set_folder = os.path.join(
            OUTPUT_FOLDER,
            "set_" + current_set_name
        )

        os.makedirs(
            set_folder,
            exist_ok=True
        )

        print(
            "Creating set_" + current_set_name
        )


        # ====================================================
        # CREATE 0s(a).txt ... 9s(a).txt
        # ====================================================

        for digit in range(10):

            start = set_number * IMAGES_PER_FILE

            end = start + IMAGES_PER_FILE

            current_images = images_by_digit[digit][
                start:end
            ]

            filename = os.path.join(
                set_folder,
                f"{digit}s({current_set_name}).txt"
            )

            write_image_file(
                filename,
                current_images
            )


    print()
    print("================================")
    print("Conversion complete!")
    print("================================")
    print()
    print("Sets created:", number_of_sets)
    print("Files per set: 10")
    print("Images per file:", IMAGES_PER_FILE)
    print(
        "Total files:",
        number_of_sets * 10
    )


if __name__ == "__main__":
    main()