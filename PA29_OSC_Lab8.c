#include <stdio.h>
#include <stdlib.h>

int main()
{
  int frames;
  int pages;
  int *frames_array;
  int *pages_array;
  int page_faults = 0;

  printf("Enter the number of frames: ");
  scanf("%d", &frames);

  printf("Enter the number of pages: ");
  scanf("%d", &pages);

  frames_array = (int *)malloc(frames * sizeof(int));

  pages_array = (int *)malloc(pages * sizeof(int));

  for (int i = 0; i < frames; i++)
  {
    frames_array[i] = -1;
  }

  printf("Enter the pages: ");
  for (int i = 0; i < pages; i++)
  {
    scanf("%d", &pages_array[i]);
  }

  printf("ReferenceString\t\t\t\t");
  printf("Frames\n");
  for (int i = 0; i < pages; i++)
  {

    int found = 0;
    for (int j = 0; j < frames; j++)
    {
      if (frames_array[j] == pages_array[i])
      {
        found = 1;
        break;
      }
    }

    if (!found)
    {
      frames_array[(page_faults % frames)] = pages_array[i];
      page_faults++;
    }

    printf("%d\t\t\t\t", pages_array[i]);
    for (int k = 0; k < frames; k++)
    {
      printf("%d   ", frames_array[k]);
    }
    printf("\n");
  }

  printf("The number of page faults is %d\n", page_faults);

  free(frames_array);
  free(pages_array);

  return 0;
}

// Output:
/*
ReferenceString                         Frames
2                               2   -1   -1   -1
3                               2   3   -1   -1
2                               2   3   -1   -1
1                               2   3   1   -1
5                               2   3   1   5
2                               2   3   1   5
4                               4   3   1   5
5                               4   3   1   5
3                               4   3   1   5
2                               4   2   1   5
5                               4   2   1   5
2                               4   2   1   5
The number of page faults is 6
*/