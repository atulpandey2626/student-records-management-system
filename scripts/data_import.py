import csv
import sqlite3
import os

DB_PATH = 'student_system.db'
CSV_PATH = 'data/sample_students.csv'

def bulk_import():
    if not os.path.exists(CSV_PATH):
        print(f"Error: Missing target source file at '{CSV_PATH}'")
        return

    try:
        conn = sqlite3.connect(DB_PATH)
        cursor = conn.cursor()
        
        with open(CSV_PATH, mode='r', encoding='utf-8') as file:
            csv_reader = csv.DictReader(file)
            
            records_inserted = 0
            for row in csv_reader:
                try:
                    cursor.execute('''
                        INSERT INTO students (name, course, year, email, cgpa)
                        VALUES (?, ?, ?, ?, ?)
                    ''', (row['name'], row['course'], int(row['year']), row['email'], float(row['cgpa'])))
                    records_inserted += 1
                except sqlite3.IntegrityError:
                    print(f"Skipping record for {row['email']} (Already exists or invalid standard)")
                    continue
        
        conn.commit()
        print(f"Successfully automated batch migration! Completed entries: {records_inserted}")
        
    except Exception as e:
        print(f"An unexpected process error occurred: {e}")
    finally:
        if conn:
            conn.close()

if __name__ == '__main__':
    bulk_import()
