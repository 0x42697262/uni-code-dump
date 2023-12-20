import sqlite3
import math
import os
DB_NAME = 'cmsc173.final_exam.iii.1.db'

dataset = {
        'sex': [1,1,1,1,0,1,0,1,1,0,0,1,1,0,1,1,0,1,1,0],
        'trestbps': [138,132,138,120,106,130,160,160,120,135,145,108,120,126,140,130,122,140,152,108],
        'chol': [175,353,282,229,223,246,164,228,240,252,307,233,237,306,335,283,213,203,223,141],
        'restecg': [1,1,0,0,1,0,0,0,1,0,0,1,1,1,1,0,1,0,1,1],
        'fbs': [0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,0],
        'target': [1,0,0,0,1,1,0,1,1,1,0,1,0,1,0,0,1,0,0,1],
        }

if not os.path.isfile('cmsc173.final_exam.iii.1.db'):
    conn = sqlite3.connect('cmsc173.final_exam.iii.1.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS my_table (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            sex INTEGER,
            trestbps INTEGER,
            chol INTEGER,
            restecg INTEGER,
            fbs INTEGER,
            target INTEGER
        )
    ''')

    for i in range(len(dataset['sex'])):
        cursor.execute('''
            INSERT INTO my_table (sex, trestbps, chol, restecg, fbs, target)
            VALUES (?, ?, ?, ?, ?, ?)
        ''', (
            dataset['sex'][i],
            dataset['trestbps'][i],
            dataset['chol'][i],
            dataset['restecg'][i],
            dataset['fbs'][i],
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

print(nb_table('sex', 'target'))
print(nb_table('restecg', 'target'))
print(nb_table('fbs', 'target'))

print('-- 1b')

print(nb_mean('trestbps', 'target', 0),  ' -- mean 0')
print(nb_stddev('trestbps', 'target', 0),  ' -- standard_deviation 0')
print(nb_mean('trestbps', 'target', 1),  ' -- mean 1')
print(nb_stddev('trestbps', 'target', 1),  ' -- standard_deviation 1')
print(nb_mean('chol', 'target', 0),  ' -- mean 0')
print(nb_stddev('chol', 'target', 0),  ' -- standard_deviation 0')
print(nb_mean('chol', 'target', 1),  ' -- mean 1')
print(nb_stddev('chol', 'target', 1),  ' -- standard_deviation 1')


print('-- 1e')
t_target1 = nb_relative_likelihood(122, 125.3, 16.640312497065672)
c_target1 = nb_relative_likelihood(200, 225.7, 44.3823037807738)
print(t_target1, ' -- x=122 | target=1')
print(c_target1, ' -- x=200 | target=1')
one = (5/10)*(c_target1*t_target1)*(3/10)*(2/10)*(5/10)
print(one)

t_target0 = nb_relative_likelihood(122, 137.7, 12.841339493993607)
c_target0 = nb_relative_likelihood(200, 261.6, 60.364080563048596)
print(t_target0, ' -- x=122 | target=0')
print(c_target0, ' -- x=200 | target=0')
zero = (8/10)*(c_target0*t_target0)*(6/10)*(3/10)*(5/10)
print(zero)

total = one+zero
print(one/total, ' -- target=1')
print(zero/total, ' -- target=0')

print('-- 1f')

