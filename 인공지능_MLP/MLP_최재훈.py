import matplotlib.pyplot as plt
import numpy as np
import math
import random

#에폭 돌린 횟수

#파일 읽기
in_f = open("tfidf.txt", "r")
test_f = open('tfidf_test.txt', 'r')

#TP, FP, FN, TN



# 테스트 파일 데이터 읽기
test_pat = []
while True:
    test_data = test_f.readline().split()
    if not test_data: break

    test_set = []
    for x in range(500):
        test_set.append(test_data[x])
    test_set.append(1)
    if test_data[500] == 'tes':
        test_data[500] = 0
    if test_data[500] == 'jso':
        test_data[500] = 0
    test_pat.append((np.array(test_set, dtype=np.float64), int(test_data[500])))
test_f.close()

#x의 값에 따라 생성되는 랜덤 숫자들을 동일하게 생성.
random.seed(0)

# calculate a random number where:  a <= rand < b
def rand(a, b):
    return (b-a)*random.random() + a

def makeMatrix(I, J, fill=0.0):
    m = []
    for i in range(I):
        m.append(np.array([fill] *J))
    return m

# our sigmoid function, tanh is a little nicer than the standard 1/(1+e^-x)
# 이진시그모이드 함수 -1~1
def sigmoid(x):
    return math.tanh(x)

# derivative of our sigmoid function, in terms of the output (i.e. y)
# 시그모이드 함수의 미분을 반환
def dsigmoid(y):
    return 1.0 - y**2

#change = lambda x : 0 if x < 0.3 else 1

class MLP:
    def __init__(self, ni, nh, no):
        # number of input, hidden, and output nodes
        self.ni = ni + 1   # +1 for bias node
        self.nh = nh   # +1 for bias node
        self.no = no

        # activations for nodes
        self.ai = [1.0]*self.ni # 501
        self.ah = [1.0]*self.nh # ?
        self.ao = [1.0]*self.no # 5

        # create weights
        self.wi = makeMatrix(self.ni , self.nh)
        self.wo = makeMatrix(self.nh, self.no)


        # set them to random values
        for i in range(self.ni):
            for j in range((self.nh-1)):
                self.wi[i][j] = rand(-0.1, 0.1)

        for j in range(self.nh):
            for k in range(self.no):
                self.wo[j][k] = rand(-0.2, 0.2)

        # last change in weights for momentum   
        self.ci = makeMatrix(self.ni, self.nh)
        self.co = makeMatrix(self.nh, self.no)

    def update(self, inputs):
        # input activations
        for i in range(self.ni-1):
            self.ai[i] = inputs[i]

        # hidden activations
        for j in range((self.nh)):
            sum = 0.0
            for i in range(self.ni):
                sum = sum + self.ai[i] * self.wi[i][j]
            self.ah[j] = sigmoid(sum)

        # output activations
        for k in range(self.no):
            sum = 0.0
            for j in range(self.nh):
                sum = sum + self.ah[j] * self.wo[j][k]
            self.ao[k] = sigmoid(sum)

        #print(self.ao)
        return self.ao[:]


    def backPropagate(self, targets, N, M):

        #델타k 구하기
        output_deltas = [0.0] * self.no

        for k in range(self.no):
            error = targets[k] - self.ao[k]
            output_deltas[k] = dsigmoid(self.ao[k]) * error

        #에타 구하기
        hidden_deltas = [0.0] * self.nh
        for j in range(self.nh):
            error = 0.0
            for k in range(self.no):
                error = error + output_deltas[k] * self.wo[j][k]
            hidden_deltas[j] = dsigmoid(self.ah[j]) * error


        #v 가중치 변화율을 구해서 업데이트
        for j in range(self.nh):
            for k in range(self.no):
                change = output_deltas[k] * self.ah[j]
                self.wo[j][k] = self.wo[j][k] + N * change * M * self.co[j][k]
                self.co[j][k] = change


        #u 가중치 변화율을 구해서 업데이트
        for i in range(self.ni):
            for j in range(self.nh):
                change = hidden_deltas[j] * self.ai[i]
                self.wi[i][j] = self.wi[i][j] + N * change + M * self.ci[i][j]
                self.ci[i][j] = change

        #오류의 정의
        error = 0.0
        for k in range(len(targets)):
            error = error + 0.5 * (targets[k] - self.ao[k]) ** 2

        return error

    def test(self, patterns):
        #TP, FP, FN, TN
        TP = [0, 0, 0, 0, 0]
        FP = [0, 0, 0, 0, 0]
        FN = [0, 0, 0, 0, 0]
        TN = [0, 0, 0, 0, 0]


        er_cnt = 0
        out_f = open("tfidf.out", "w")

        for p in patterns:
            soft_sum = 0
            soft_list = []
            temp = self.update(p[0])

            #soft_max
            for data in temp:
                soft_sum += data
            for for_idx in range(len(temp)):
                soft_list.append(temp[for_idx] / soft_sum)

            result = soft_list.index(max(soft_list))

            if (result+1) !=  p[1]:
                er_cnt += 1
                FN[p[1]-1] += 1
                FP[result] += 1
            else :
                TP[result] += 1
                for x in range(5):
                    if result == x:
                        continue
                    TN[x] += 1

        print("틀린 갯수 : " + str(er_cnt))
        print("총 갯수 : " + str(len(patterns)))
        accurancy = (len(patterns) - er_cnt) / len(patterns)
        print("Accurancy = " + str(accurancy))
        Precision = []
        for x in range(5):
            if TP[x] + FP[x] == 0:
                continue
            Precision.append(TP[x] / (TP[x]+FP[x]))
        print("Precision = " + str(Precision))
        Recall = []
        for x in range(5):
            if TP[x] + FN[x] == 0:
                continue
            Recall.append(TP[x] / (TP[x] + FN[x]))
        print("Recall = " + str(Recall))
        print("------------")

        out_f.close()

    def weights(self):
        print("input weights:")
        for i in range(self.ni):
            print(self.wi[i])
        print()
        print("output weights:")

        for j in range(self.nh):
            print(self.wo[j])

    def train(self, patterns, iterations=50, N=0.1, M=0.1):
        #N은 Learning rate
        #M은 깊은 네트워크에서 속도향상 방법(momentum factor)
        #iterations은 반복횟수

        error_data = []
        end = False
        for i in range(iterations):
            if(end) : break
            error = 0.0

            for p in patterns:
                inputs = p[0] #입력값
                targets = [p[1]] #정답
                
                
                #[0,0,0,0, 1] 처럼 만들기
                answer_list = []
                for x in range(5):
                    answer_list.append(0)
                for x in range(5):
                    if (targets[0] -1)  == x:
                        answer_list[x] = 1
                #print(answer_list)
                #전방계산
                self.update(inputs)

                #오류 역전파
                error = error + self.backPropagate(answer_list, N, M)

            print('epoch ' + str(i+1))
            self.test(test_pat)

def demo():
    # 입력값
    pat = []
    while True:
        input_data = in_f.readline().split()
        if not input_data : break #더 이상 읽을 것이 없다면 끝
        #pat.append((np.array([input_data[0], input_data[1], input_data[2], 1], dtype=np.float64), int(input_data[3])))

        input_set = []
        for x in range(500):
            input_set.append(input_data[x])
        input_set.append(1)
        if input_data[500] == 'tes':
            input_data[500] = 0
        pat.append((np.array(input_set,dtype=np.float64), int(input_data[500])))
        #print(pat)

    in_f.close()

    #노드와 레이어 생성
    n = MLP(500, 100, 5)  #클래스 NN 에서 각각 층의 노드 갯수 생성


    #트레이닝
    n.train(pat)

    #TEST




    #n.test(test_pat)

    #weight
    #n.weights()

demo()
