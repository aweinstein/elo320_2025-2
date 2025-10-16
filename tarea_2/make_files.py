import pandas as pd

# Read the CSV file (semicolon-separated)
fn = 'household_power_consumption.txt'
df = pd.read_csv(fn, sep=';', low_memory=False, na_values=['?'])


# Combine 'Date' and 'Time' into a single datetime column
df['Datetime'] = pd.to_datetime(df['Date'] + ' ' + df['Time'],
                                dayfirst=True, errors='coerce')

# Remove NaNs
df = df.dropna(subset=['Datetime', 'Global_active_power'])

df['unix_time'] = df['Datetime'].astype('int64') // 10**9

# Keep only unix time and active power
df = df[['unix_time', 'Global_active_power']]

for l in [len(df) // 2**i for i in range(6)]:
    fn = f'data_power_{l}.csv'
    df[:l].to_csv(fn, index=False)
    print(f'CSV file {fn} saved.')
