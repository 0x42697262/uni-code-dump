import math

dataset = {
        'sex': [1,1,1,1,0,1,0,1,1,0,0,1,1,0,1,1,0,1,1,0],
        'trestbps': [138,132,138,120,106,130,160,160,120,135,145,108,120,126,140,130,122,140,152,108],
        'chol': [175,353,282,229,223,246,164,228,240,252,307,233,237,306,335,283,213,203,223,141],
        'restecg': [1,1,0,0,1,0,0,0,1,0,0,1,1,1,1,0,1,0,1,1],
        'fbs': [0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,0],
        'target': [1,0,0,0,1,1,0,1,1,1,0,1,0,1,0,0,1,0,0,1],
        }


def manhattan(sample: list):

    sex = sample[0]
    trestbps = sample[1]
    chol = sample[2]
    restecg = sample[3]
    fbs = sample[4]
    new = []
    for i in range(len(dataset['target'])):
        distance = abs(dataset['sex'][i] - sex) + \
                abs(dataset['trestbps'][i] - trestbps) + \
                abs(dataset['chol'][i] - chol) + \
                abs(dataset['restecg'][i] - restecg) + \
                abs(dataset['fbs'][i] -  fbs)
        new.append({distance : dataset['target'][i]})

    return new

def euclidian(sample: list):
    sex = sample[0]
    trestbps = sample[1]
    chol = sample[2]
    restecg = sample[3]
    fbs = sample[4]
    new = []
    for i in range(len(dataset['target'])):
        total = (dataset['sex'][i] - sex)**2
        total += (dataset['trestbps'][i] - trestbps)**2
        total += (dataset['chol'][i] - chol )**2
        total += (dataset['restecg'][i] - restecg )**2
        total += (dataset['fbs'][i] - fbs)**2
        distance = math.sqrt(total)
        new.append({distance : dataset['target'][i]})

    return new


m = (manhattan([1,122, 200, 0, 1]))
e = (euclidian([1,122, 200, 0, 1]))
m2 = sorted(m, key=lambda d: list(d.keys())[0])
for _ in m:
    print(_)
print(m2[:5])

e2 = sorted(e, key=lambda d: list(d.keys())[0])
for _ in e:
    print(_)
print(e2[:5])




