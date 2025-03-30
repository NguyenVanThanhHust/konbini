import sqlite3

# Connect to database
connection = sqlite3.connect("sample.db")

# cursor
cursor = connection.cursor()

# execute some sql command
sql_cmd_create_table = '''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT,
    age INTEGER
)
'''
cursor.execute(sql_cmd_create_table)

sql_cmd_insert_data = 'INSERT INTO users (name, age) VALUES ("Alice", 25)'
cursor.execute(sql_cmd_insert_data)

sql_cmd_search_data = "SELECT * FROM users"
cursor.execute(sql_cmd_search_data)

# Fake 3 names
names = ['name1', 'name2', 'name3']
 
# Fake 3 ages
ages = [1, 2, 3]

# Primary keys
pk = [2, 3, 4]
for i in range(3):
    # This is the q-mark style:
    cursor.execute(f'INSERT INTO users (name, age) VALUES ("{names[i]}", "{ages[i]}")')

# Query the data
cursor.execute("SELECT * FROM users")

rows = cursor.fetchall()
for row in rows:
    print(row)

connection.commit()
connection.close()
