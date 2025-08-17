for (int i = 0;i < 864;i++)
    {
        int row = i % 36;
        int colum = i % 24;
       if (what_boxes_in_the_middle_are_on[row][colum] == true)
        {
            DrawRectangle(596 + (17 * colum), 238 + (17 * row), 17, 17, BLACK);    
        }
    }