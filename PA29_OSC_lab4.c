#include <stdio.h>
#include <pthread.h>

// Function to perform addition
void *addition(void *arg)
{
    int result = 10 + 5;
    printf("Addition result: %d\n", result);
    pthread_exit(NULL);
}

// Function to perform subtraction
void *subtraction(void *arg)
{
    int result = 10 - 5;
    printf("Subtraction result: %d\n", result);
    pthread_exit(NULL);
}

// Function to perform multiplication
void *multiplication(void *arg)
{
    int result = 10 * 5;
    printf("Multiplication result: %d\n", result);
    pthread_exit(NULL);
}

// Function to perform division
void *division(void *arg)
{
    int result = 10 / 5;
    printf("Division result: %d\n", result);
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[4];

    // Create four threads for each operation
    pthread_create(&threads[0], NULL, addition, NULL);
    pthread_create(&threads[1], NULL, subtraction, NULL);
    pthread_create(&threads[2], NULL, multiplication, NULL);
    pthread_create(&threads[3], NULL, division, NULL);

    // Wait for all threads to finish
    for (int i = 0; i < 4; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

// Output:
/*
Addition result: 15
Subtraction result: 5
Division result: 2
Multiplication result: 50
*/