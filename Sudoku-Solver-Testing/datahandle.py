import csv

data_average = {}

with open('output.csv', newline='') as csvfile:
    reader = csv.reader(csvfile)
    
    # Skip the first 1 lines
    next(reader)

    for row in reader:
        key = int(row[1])
        solving_time_ms = float(row[2])
        backtrack_count = int(row[3])
        propagation_count = int(row[4])

        if key not in data_average:
            data_average[key] = [1,solving_time_ms,backtrack_count,propagation_count]
        else:
            data_average[key][0] += 1
            data_average[key][1] += solving_time_ms
            data_average[key][2] += backtrack_count
            data_average[key][3] += propagation_count

with open('output_average.csv', 'w', newline='') as csvfile:
    writer = csv.writer(csvfile)
    writer.writerow(['key', 'solving_time_ms', 'backtrack_count', 'propagation_count'])
    
    for key, values in data_average.items():
        count = values[0]
        solving_time_ms = values[1] / count
        backtrack_count = values[2] / count
        propagation_count = values[3] / count
        writer.writerow([key, solving_time_ms, backtrack_count, propagation_count])



    