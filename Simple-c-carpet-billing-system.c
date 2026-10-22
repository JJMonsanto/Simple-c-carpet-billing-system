#include <stdio.h>

#define LABOR_COST 0.35
#define TAX 0.085

void getInput(int *length, int *width, int *discount, double *costPerSquareFoot);

void calcInstalledPrice(int length, int width, double costPerSquareFoot,
                        int *area, double *carpetCost, double *laborCost, double *installedPrice);

void calcSubtotal(double installedPrice, int discount, double *discountAmount, double *subtotal);

void calcTotal(double subtotal, double *tax, double *totalPrice);

void calcAll(int length, int width, int discount, double costPerSquareFoot,
             int *area, double *carpetCost, double *laborCost, double *installedPrice,
             double *discountAmount, double *subtotal, double *tax, double *totalPrice);

int main(void) {
    int length, width, discount, area;
    double costPerSquareFoot, carpetCost, laborCost, installedPrice;
    double discountAmount, subtotal, tax, totalPrice;

    getInput(&length, &width, &discount, &costPerSquareFoot);

    calcAll(length, width, discount, costPerSquareFoot,
            &area, &carpetCost, &laborCost, &installedPrice,
            &discountAmount, &subtotal, &tax, &totalPrice);

    printf("\n                        MEASUREMENT\n");
    printf("Length                                      %d ft\n", length);
    printf("Width                                       %d ft\n", width);
    printf("Area                                       %d square ft\n", area);

    printf("\n                        CHARGES\n");
    printf("DESCRIPTION             COST/SQ. FT.        CHARGE\n");
    printf("--------------------------------------------------\n");
    printf("Carpet                  %.2f              $%.2f\n", costPerSquareFoot, carpetCost);
    printf("Labor                   %.2f               %.2f\n", LABOR_COST, laborCost);
    printf("INSTALLED PRICE                           $%.2f\n", installedPrice);
    printf("Discount                %d %%                %.2f\n", discount, discountAmount);
    printf("SUBTOTAL                                  $%.2f\n", subtotal);
    printf("Tax                                        %.2f\n", tax);
    printf("TOTAL                                     $%.2f\n", totalPrice);

    return 0;
}

void getInput(int *length, int *width, int *discount, double *costPerSquareFoot) {
    printf("Length of room (feet)?           ");
    scanf("%d", length);
    printf("Width of room (feet)?            ");
    scanf("%d", width);
    printf("Customer discount (percent)?     ");
    scanf("%d", discount);
    printf("Cost per square foot (xxx.xx)?   ");
    scanf("%lf", costPerSquareFoot);
}

void calcInstalledPrice(int length, int width, double costPerSquareFoot,
                        int *area, double *carpetCost, double *laborCost, double *installedPrice) {
    *area = length * width;
    *carpetCost = *area * costPerSquareFoot;
    *laborCost = *area * LABOR_COST;
    *installedPrice = *carpetCost + *laborCost;
}

void calcSubtotal(double installedPrice, int discount, double *discountAmount, double *subtotal) {
    *discountAmount = installedPrice * (discount / 100.0);
    *subtotal = installedPrice - *discountAmount;
}

void calcTotal(double subtotal, double *tax, double *totalPrice) {
    *tax = subtotal * TAX;
    *totalPrice = subtotal + *tax;
}

void calcAll(int length, int width, int discount, double costPerSquareFoot,
             int *area, double *carpetCost, double *laborCost, double *installedPrice,
             double *discountAmount, double *subtotal, double *tax, double *totalPrice) {
    calcInstalledPrice(length, width, costPerSquareFoot, area, carpetCost, laborCost, installedPrice);
    calcSubtotal(*installedPrice, discount, discountAmount, subtotal);
    calcTotal(*subtotal, tax, totalPrice);
}
