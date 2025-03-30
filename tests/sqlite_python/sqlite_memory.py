import sqlite3

def main():
    # Step 1: Open the database file from disk
    disk_conn = sqlite3.connect("sample.db")  # Replace with your database file name
    print("Opened disk database 'example.db'.")

    # Step 2: Create an in-memory database
    memory_conn = sqlite3.connect(":memory:")
    print("Created in-memory database.")

    try:
        # Step 3: Load data from the disk database into the in-memory database
        disk_conn.backup(memory_conn)
        print("Data copied from disk database to in-memory database.")

        # Step 4: Use the in-memory database for operations
        cursor = memory_conn.cursor()
        cursor.execute("SELECT name FROM sqlite_master WHERE type='table';")
        tables = cursor.fetchall()
        print("\nTables in the in-memory database:")
        for table in tables:
            print(table[0])

        cursor.execute("SELECT * FROM users LIMIT 5;")
        rows = cursor.fetchall()
        print("\nSample data from the in-memory database:")
        for row in rows:
            print(row)

    finally:
        # Step 5: Close connections
        disk_conn.close()
        memory_conn.close()
        print("\nConnections closed.")

if __name__ == "__main__":
    main()
