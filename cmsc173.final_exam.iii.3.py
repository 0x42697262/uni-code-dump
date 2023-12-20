import sqlite3
import math
import os
DB_NAME = 'cmsc173.final_exam.iii.3.db'

dataset = {
        'Age': [36,37,27,65,40,52,50,20,45,30,49,41,47,59,47,42,37,32,28,22],
        'Varices': [1,1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1],
        'Albumin': [4.2,4.2,3.0,2.9,4.2,4.0,2.4,3.9,3.0,3.9,3.7,3.9,2.6,3.6,2.1,4.0,4.0,4.0,4.9,4.2],
        'Malaise': [1,1,1,0,0,1,1,0,1,1,0,1,0,0,0,1,0,1,1,1],
        'Histology': [0,0,1,1,1,0,1,0,0,0,0,0,1,1,1,1,0,0,0,0],
        'target': [1,0,1,1,1,1,0,1,1,1,1,1,0,0,0,1,1,1,1,1],
        }

if not os.path.isfile(DB_NAME):
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS my_table (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            Age INTEGER,
            Varices INTEGER,
            Albumin FLOAT,
            Malaise INTEGER,
            Histology INTEGER,
            target INTEGER
        )
    ''')

    for i in range(len(dataset['Age'])):
        cursor.execute('''
            INSERT INTO my_table (Age, Varices, Albumin, Malaise, Histology, target)
            VALUES (?, ?, ?, ?, ?, ?)
        ''', (
            dataset['Age'][i],
            dataset['Varices'][i],
            dataset['Albumin'][i],
            dataset['Malaise'][i],
            dataset['Histology'][i],
            dataset['target'][i],
        ))

    conn.commit()
    conn.close()

def nb_sum(feature, classname=None, value=None):
    conn    = sqlite3.connect(DB_NAME)
    cursor  = conn.cursor()
    if not classname:
        cursor.execute(f'''
            SELECT sum({feature})
            FROM my_table
        ''')
    else:
        cursor.execute(f'''
            SELECT sum({feature})
            FROM my_table
            WHERE {classname} = {value}
        ''')

    result = cursor.fetchall()[0][0]
    conn.close()

    return (feature, result)

def nb_table(feature, classname):
    conn    = sqlite3.connect(DB_NAME)
    cursor  = conn.cursor()

    table = {}
    feature_values = list(set(dataset[feature]))
    class_values = list(set(dataset[classname]))
    for cvalue in class_values:
        table[cvalue] = {}
        for fvalue in feature_values:
            cursor.execute(f"""
                           SELECT COUNT({feature}) FROM my_table
                           WHERE {classname} = {cvalue}
                           AND
                           {feature} = {fvalue}
                           """)
            table[cvalue][fvalue] = cursor.fetchall()[0][0]

    conn.close()

    return (feature, table)

def nb_count(feature, classname = None, value = None):
    conn    = sqlite3.connect(DB_NAME)
    cursor  = conn.cursor()
    if not classname:
        cursor.execute(f"""
                       SELECT COUNT({feature}) FROM my_table
                       """)
    else:
        cursor.execute(f"""
                       SELECT COUNT({feature}) FROM my_table
                       WHERE {classname} = {value}
                       """)
    result = cursor.fetchone()[0]
    conn.close()

    return result


def nb_mean(feature, classname = None, value = None):
    conn    = sqlite3.connect(DB_NAME)
    cursor  = conn.cursor()
    if not classname:
        cursor.execute(f"""
                       SELECT COUNT({feature}) FROM my_table
                       """)
    else:
        cursor.execute(f"""
                       SELECT COUNT({feature}) FROM my_table
                       WHERE {classname} = {value}
                       """)

    result =  nb_sum(feature, classname, value)[1] / nb_count(feature, classname, value)
    conn.close()

    return (feature, result)

def nb_stddev(feature,classname=None,value=None):
    conn    = sqlite3.connect(DB_NAME)
    cursor  = conn.cursor()
    mean = nb_mean(feature,classname,value)[1]
    count = nb_count(feature,classname,value)

    if not classname:
        cursor.execute(f"""
                       SELECT {feature} FROM my_table
                       """)
    else:
        cursor.execute(f"""
                       SELECT {feature} FROM my_table
                       WHERE {classname} = {value}
                       """)

    data = cursor.fetchall()
    conn.close()

    total = 0
    for d in data:
        total += (d[0]-mean)**2
    result = math.sqrt(total / (count - 1))

    return (feature, result)

def nb_relative_likelihood(x, μ, σ):
    exponent = -(1/2)*(((x-μ)/σ)**2)
    return (1/(σ*math.sqrt(2*math.pi)))*(math.e**exponent)



print('-- 1a')

print(nb_table('Varices', 'target'))
print(nb_table('Malaise', 'target'))
print(nb_table('Histology', 'target'))

print('-- 1b')

print(nb_mean('Age', 'target', 0),  ' -- mean 0')
print(nb_mean('Age', 'target', 1),  ' -- mean 1')
print(nb_stddev('Age', 'target', 0),  ' -- standard_deviation 0')
print(nb_stddev('Age', 'target', 1),  ' -- standard_deviation 1')
print(nb_mean('Albumin', 'target', 0),  ' -- mean 0')
print(nb_mean('Albumin', 'target', 1),  ' -- mean 1')
print(nb_stddev('Albumin', 'target', 0),  ' -- standard_deviation 0')
print(nb_stddev('Albumin', 'target', 1),  ' -- standard_deviation 1')


print('-- 1e')
age0 = nb_relative_likelihood(35, 48, 7.874007874011811)
albumin0 = nb_relative_likelihood(2.2, 2.98, 0.8843076387773658)
print(age0, ' -- x=35 | target=0')
print(albumin0, ' -- x=2.2 | target=0')
zero = (3/5)*(age0*albumin0)*(5/15)*(1/5)*(5/20)
print(zero)

age1 = nb_relative_likelihood(35, 37.73, 12.03843052577077)
albumin1 = nb_relative_likelihood(2.2, 3.853, 0.5303188618539749)
print(age1, ' -- x=35 | target=1')
print(albumin1, ' -- x=2.2 | target=1')
one = (2/5)*(age1*albumin1)*(10/15)*(4/5)*(15/20)
print(one)

total = one+zero
print(one/total, ' -- target=0')
print(zero/total, ' -- target=1')
print(total)

print('-- 1f')

