# Simple C Carpet Company Customer Billing System

A modular, defensive C application that computes customer itemized bills and measurement receipts for a commercial carpet and flooring installation company. Demonstrates structured multi-function pipeline coordination and memory address passing (pointer out-parameters) to overcome C's single-return limitation cleanly.

---

## Architectural Pipeline

The program follows a modular pipeline architecture where `main(void)` acts purely as a top-level coordinator delegating input, calculation, and output to specialized routines:

```text
                                         [ main(void) ]
                                                |
            +-----------------------------------+-----------------------------------+
            |                                   |                                   |
            v                                   v                                   v
       [ getInput ]                         [ calcAll ]                      [ printResults ]
     (reads via addresses)             (calculation hub)                    (output coordinator)
                                                |                                   |
                          +---------------------+-----------+               +-------+-------+
                          |                     |           |               |               |
                          v                     v           v               v               v
                [ calcInstalledPrice ]   [ calcSubtotal ] [ calcTotal ] [ printMeasurements ] [ printCharges ]
                - Computes Area          - Computes Disc. - Computes Tax - Prints room specs  - Prints itemized
                - Computes Carpet Cost   - Computes Subt. - Computes Tot.                      statement
                - Computes Labor Cost
                - Computes Inst. Price
```

---

## ?? Mathematical Formulation

Fixed business constants:
- **Labor Rate:** `$0.35` per square foot (`LABOR_COST`)
- **Tax Rate:** `8.5%` applied post-discount (`TAX`)

Formulas:
1. $\text{Area} = \text{Length} \times \text{Width}$
2. $\text{Carpet Cost} = \text{Area} \times \text{Cost per Sq. Ft.}$
3. $\text{Labor Cost} = \text{Area} \times \text{LABOR\_COST}$
4. $\text{Installed Price} = \text{Carpet Cost} + \text{Labor Cost}$
5. $\text{Discount Amount} = \text{Installed Price} \times \left(\frac{\text{Discount \%}}{100.0}\right)$
6. $\text{Subtotal} = \text{Installed Price} - \text{Discount Amount}$
7. $\text{Tax} = \text{Subtotal} \times \text{TAX}$
8. $\text{Total Bill} = \text{Subtotal} + \text{Tax}$

---

## ?? Empirical Verification & Test Matrix

Compiled using `gcc -Wall -Wextra -Werror` and empirically verified against standard multi-case test datasets:

| Test Case | Room Length | Room Width | Discount % | Cost / Sq. Ft. | Installed Price | Discount Amt | Subtotal | Tax (8.5%) | Total Bill | Status |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **Standard Room** | 30 ft | 18 ft | 9% | $8.23 | **$4,633.20** | $416.99 | **$4,216.21** | $358.38 | **$4,574.59** | **PASS** |
| **Dataset 1** | 23 ft | 13 ft | 12% | $14.20 | **$4,350.45** | $522.05 | **$3,828.40** | $325.41 | **$4,153.81** | **PASS** |
| **Zero Discount** | 35 ft | 8 ft | 0% | $8.00 | **$2,338.00** | $0.00 | **$2,338.00** | $198.73 | **$2,536.73** | **PASS** |
| **High Unit Cost** | 14 ft | 11 ft | 10% | $22.25 | **$3,480.40** | $348.04 | **$3,132.36** | $266.25 | **$3,398.61** | **PASS** |

---

## ?? Compilation & Execution

```bash
gcc -Wall -Wextra -Werror Simple-c-carpet-billing-system.c -o carpet_billing
./carpet_billing
```

### Sample Output:
```text
Length of room (feet)?           30
Width of room (feet)?            18
Customer discount (percent)?     9
Cost per square foot (xxx.xx)?   8.23

                        MEASUREMENT
Length                                      30 ft
Width                                       18 ft
Area                                       540 square ft

                        CHARGES
DESCRIPTION             COST/SQ. FT.        CHARGE
--------------------------------------------------
Carpet                  8.23              $4444.20
Labor                   0.35               189.00
INSTALLED PRICE                           $4633.20
Discount                9 %                416.99
SUBTOTAL                                  $4216.21
Tax                                        358.38
TOTAL                                     $4574.59
```

---

## ??? Static Safety Audit
Scanned using static analysis security scanner:
- Unsafe unbounded calls (`gets`, bare `scanf("%s")`): **0 findings**
- Shell injection / pipe traps: **0 findings**
- Precision consistency: `double` used uniformly across all monetary and decimal calculations.
