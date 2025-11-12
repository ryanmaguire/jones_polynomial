#include <stdio.h>
#include <math.h>
#include "int_polynomial/int_polynomial.h"
#include "double_matrix/double_matrix.h"
#include "int_polynomial_matrix/int_polynomial_matrix.h"
#include "pd_code/pd_code_knot.h"

int main()
{
    /*struct int_polynomial poly1 = new_int_polynomial(3);
    struct int_polynomial poly2 = new_int_polynomial(4);

    int a[4] = { 1,3,-3,1 };
    int b[5] = { 1,-4,6,-4,1 };

    poly1.coeffs = a;
    poly2.coeffs = b;

    print_int_polynomial(poly1, 't');
    print_int_polynomial(poly2, 't');

    print_int_polynomial(add_int_polynomial(poly1, poly2), 't');
    print_int_polynomial(multiply_int_polynomial(poly1, poly2), 't');*/

    /*struct double_matrix L = new_double_matrix(3, 3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            L.entries[i][j] = (i + j) * (i + j);
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%f  ", L.entries[i][j]);
        }
        printf("\n");
    }

    int det = round(determinant_double_matrix(L));
    printf("Determinant: %d\n", det);
    printf("Matrix after REF:\n");

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%f  ", L.entries[i][j]);
        }
        printf("\n");
    }*/

    /*struct int_polynomial_matrix A = new_int_polynomial_matrix(3, 3);

    struct int_polynomial one_minus_t_poly = new_int_polynomial(1);
    one_minus_t_poly.coeffs[0] = 1;
    one_minus_t_poly.coeffs[1] = -1;

    struct int_polynomial t_poly = new_int_polynomial(1);
    t_poly.coeffs[0] = 0;
    t_poly.coeffs[1] = 1;

    struct int_polynomial minus_one_poly = new_int_polynomial(0);
    minus_one_poly.coeffs[0] = -1;

    struct int_polynomial zero_poly = new_int_polynomial(0);
    zero_poly.coeffs[0] = 0;

    //char* specs = "203210312";
    char* specs = "012123231";
    int index = 0;
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.cols; j++) {
            switch (specs[index]) {
            case '0':
                A.entries[i][j] = zero_poly;
                break;
            case '1':
                A.entries[i][j] = minus_one_poly;
                break;
            case '2':
                A.entries[i][j] = t_poly;
                break;
            case '3':
                A.entries[i][j] = one_minus_t_poly;
                break;
            }
            index++;
        }
    }

    printf("Elements of matrix A:\n");
    print_int_polynomial_matrix(A, 't', 14);
    printf("\n");

    struct int_polynomial result = determinant_int_polynomial_matrix(A, -1);
    printf("Determinant of A: ");
    print_int_polynomial(result, 't');
    printf("\n\n\n");*/

    unsigned int raw_specs[] = {1,4,2,5,3,8,4,9,5,12,6,13,9,1,10,14,13,11,14,10,11,6,12,7,7,2,8,3};
    int num_crossings = 7;
    unsigned int* specs = malloc(num_crossings * 4 * sizeof(int));
    for (int i = 0; i < num_crossings * 4; i++) {
        specs[i] = raw_specs[i] - 1;
    }

    struct crossing temp_crossing = { {specs[0], specs[1], specs[2], specs[3]} };
    struct pd_code_node* previous = new_pd_code_node(&temp_crossing);
    struct pd_code_node* head = previous;
    for (int i = 1; i < num_crossings; i++) {
        struct crossing* temp_crossing = malloc(sizeof(struct crossing));
        for (int j = 0; j < 4; j++) {
            temp_crossing->arcs[j] = specs[4 * i + j];
        }
        struct pd_code_node* current = new_pd_code_node(temp_crossing);
        previous->next = current;
        current->prev = previous;
        previous = current;
    }

    printf("Given PD code:\n");
    for (int i = 0; i < num_crossings; i++) {
        printf("%d %d %d %d\n", head->tuple->arcs[0] + 1, head->tuple->arcs[1] + 1, head->tuple->arcs[2] + 1, head->tuple->arcs[3] + 1);
        head = head->next;
    }

    printf("\nCalculated Alexander Polynomial:\n");

    struct int_polynomial result = pd_code_alexander_polynomial(previous);
    print_int_polynomial(result, 't');

    printf("\n\n\n");

    return 0;
}