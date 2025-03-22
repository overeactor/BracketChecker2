
#include <stdio.h>
int main() {
    printf("Hello, world!\n");
    return 0;
}


#include <stdio.h>
int main() {
    printf("Hello, world!\n");
    return 0;


#include <stdio.h>
int main() {
    // Этот комментарий содержит { [ ( ) ] }
    printf("Hello, world!\n");
    return 0;
}

#include <stdio.h>
int main() {
    /* Комментарий: начало { [ ( без закрывающей части */
    printf("Hello, world!\n");
    return 0;
}

#include <stdio.h>
int main() {
    printf("Hello, world!\n");
    return 0;
}}


#include <stdio.h>
void foo(int a[5]) {
    for (int i = 0; i < 5; i++) {
        printf("Value: %d\n", a[i]);
    }
}
int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    foo(arr);
    return 0;
}


#include <stdio.h>
int main() {
    printf("Hello, world!\n";
    return 0;
}


#include <stdio.h>
int main() {
    /* 
    if (1) {
        printf("Этот код закомментирован и содержит ошибку: (");
    }
    */
    printf("Hello, world!\n");
    return 0;
}


#include <stdio.h>
int main() {
    // Однострочный комментарий: ( ] } [
    /* Многострочный комментарий:
       {
       [
       )
    */
    printf("Hello, world!\n");
    return 0;
}


#include <stdio.h>
int main() {
    int arr[3] = {1, 2, 3};
    printf("Array element: %d\n", arr[0]);
    return 0;
}

