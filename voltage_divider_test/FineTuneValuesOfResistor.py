def calculate_vin(vout, r1, r2):
    vin = vout * (r1 + r2) / r2
    return vin

def main():
    try:
        r1 = float(input("Enter R1 in ohms: "))
        r2 = float(input("Enter R2 in ohms: "))
        vout = float(input("Enter Vout in volts: "))

        vin = calculate_vin(vout, r1, r2)
        print(f"Calculated Vin: {vin:.2f} V")

    except ValueError:
        print("Please enter valid numeric values.")

while __name__ == "__main__":
    main()
