import csv

def update_csv_file(input_file, output_file):
    with open(input_file, 'r') as file:
        reader = csv.reader(file)
        rows = list(reader)  # Read all rows into a list

        # Make changes to the desired columns
        for row in rows:
            # Copy first 8 characters of column P (16th column) to column I (9th column)
            if len(row) > 15:
                value_p = row[15]
                row[8] = value_p[:8]

            # Add 1014 to column X (24th column)
            if len(row) > 23:
                value_x = row[23]
                if value_x.isdigit():
                    row[23] = str(int(value_x) + 1014)
                else:
                    row[23] = '1014'  # If the value is not a number, set it to 1014 directly

    with open(output_file, 'w', newline='') as file:
        writer = csv.writer(file)
        writer.writerows(rows)

    print(f"Changes saved to {output_file}.")

# Example usage:
input_file = 'input.csv'
output_file = 'output.csv'
update_csv_file(input_file, output_file)


