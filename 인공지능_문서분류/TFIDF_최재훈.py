#-*- coding: utf-8 -*-

import os
import sys
import json
from pprint import pprint
import re
import operator
import math

# 전역변수
IDFdict = {}

# 파일 열기
with open('Tr.json', encoding='ISO-8859-1') as data_file:
    data = json.loads(data_file.read())


# idf 딕셔너리 에 단어 넣기
def MakeIDFdic(NounList):
    # TF dictionary 만들기
    for tmp in NounList:
        idx = tmp.find('/')
        if len(tmp[:idx]) > 1:
            IDFdict.update({tmp: 0})
    # print(TFdic.items())

    # 한개 문서의 명사들을 리스트로 만듬


#/N이후 자르기 -> 이중 리스트 분리
def SliceNoun(NounLineList):
    # /N~ 자르고 하나의 리스트에 넣기.
    #tempList = []
    #for tmp in NounLineList:
    #    for tmp_2 in tmp:
    #        idx = tmp_2.find('/')
    #        tempList.append(tmp_2[:idx])
    # NounList 정렬
    #tempList.sort()
    # print(NounList)
    #return tempList

    #리스트 이중구조 분리
    tempList = []
    for tmp in NounLineList:
        for tmp_2 in tmp:
            tempList.append(tmp_2)
    tempList.sort()

    return tempList


# 문서마다 명사들을 추출하는 함수
def loadNoun(DocIdx):
    NounLineList = []
    NounList = []
    for x in data[DocIdx].get('sentence'):
        # print(x.encode('ISO-8859-1').decode('euc-kr'))

        # 명사들 리스트에 넣기
        if re.search('/N[a-zA-Z]+', x.encode('iso-8859-1').decode('euc-kr', 'ignore')):
            # print(re.findall('[가-힣]+/N[a-zA-Z]+', x.encode('ISO-8859-1').decode('euc-kr')))
            NounLineList.append(re.findall('[가-힣]+,?.?/N[a-zA-Z]+', x.encode('iso-8859-1').decode('euc-kr', 'ignore')))

    NounList = SliceNoun(NounLineList)
    #print(NounList)
    # 문서마다 나온 명사 단어들을 파일로 저장
    doc_f = open('./doc_tf/doc_' + str(DocIdx) + '.txt', 'w')
    for in_data in NounList:
        doc_f.write(in_data + '\n')
    doc_f.close()

    MakeIDFdic(NounList)


# IDFdict Value값 계산
def IDFdict_value_count(doc_idx):
    # 파일 불러오기
    doc_file = open('./doc_tf/doc_' + str(doc_idx) + '.txt', 'r')
    doc_word = doc_file.readlines()
    # 리스트에 저장
    for idx in range(len(doc_word)):
        doc_word[idx] = doc_word[idx].replace('\n', '')
    # print(doc_word)

    # 중복 제거
    # set은 순서를 유지하지 않고 중복을 제거
    doc_word = list(set(doc_word))
    # print(doc_word)

    # 딕셔너리의 값과 비교해서 value 증가시키기
    for idx in range(len(doc_word)):
        word = str(doc_word[idx])

        # IDF딕셔너리에 있다면 증가
        if (word in IDFdict) == True:
            value = IDFdict[word] + 1
            IDFdict.update({word: value})

    doc_file.close()

#answer 리스트에 저장하기
def answer_save(idx):
    tmpList = []
    for x in range(idx):
        if data[x].get('answer') == 'tes':
            tmpList.append(data[x].get('answer'))
            continue
        tmpList.append(int(data[x].get('answer')))
    return tmpList


def TFIDF_cal(docNum,df_list, topWord_list):
    #문서 X의 TF계산
    doc_tf = {}
    for content in topWord_list:
        doc_tf.update({content:0})
    doc_file = open('./doc_tf/doc_' + str(docNum) + '.txt', 'r')
    while True:
        txtWord = doc_file.readline()
        txtWord = txtWord.replace('\n', '')

        if  txtWord == '':
            break
        if (txtWord in doc_tf) == True :
            val = doc_tf[txtWord] + 1
            doc_tf.update( {txtWord:val} )
    #print(doc_tf)

    #문서 X의 IDF 계산
    doc_idf = {}
    for content in topWord_list:
        doc_idf.update( {content:0} )
    for index in range(500):
        key = df_list[index][0]
        value = math.log(3480/df_list[index][1], 2)
        doc_idf.update( {key : value} )
    #print(doc_idf)

    #문서 X의 TFIDF 계산
    doc_tfidf = {}
    for topWord in topWord_list :
        tfidf = doc_tf[topWord] * doc_idf[topWord]
        #print(tfidf)
        doc_tfidf.update( {topWord : tfidf})
    #print(doc_tfidf)
    
    #문서 X의 TFIDF 정규화
    sum_tfidf = 0.0
    doc_nomal = {}
    for x in topWord_list:
        sum_tfidf += doc_tfidf[x] * doc_tfidf[x]
    sum_tfidf = math.sqrt(sum_tfidf)
    #print(sum_tfidf)
    for x in topWord_list:
        if sum_tfidf == 0:
            nomal_val = 0
        else :
            nomal_val = doc_tfidf[x] / sum_tfidf
        doc_nomal.update({x:nomal_val})
    #print(doc_nomal)


    tfidf_file = open('./tfidf.txt', 'a')
    for x in topWord_list:
        tfidf_file.write(str(doc_nomal[x]) + ' ')
    tfidf_file.close()



# MAIN 시작
Document_idx = 3480 # 총.3480 인덱스 110 문서에서 정규표현식 오류

#정답저장하기
answerList = answer_save(Document_idx)
#print(answerList)

# 일정한 차원의 Dictionary 만들기
for loop_count in range(Document_idx):
    loadNoun(loop_count)

# IDFdict의 value값
# 문서를 돌면서 단어들 확인.(각 문서별로 만들어진 파일을 활용)
for loop_count in range(Document_idx):
    IDFdict_value_count(loop_count)
#print(IDFdict)

#dictionary value 순으로 정렬
#리스트안의 튜플로 전환됨
IDFdict_sorting = sorted(IDFdict.items(), key=operator.itemgetter(1), reverse=True)
#print(IDFdict_sorting)

#상한 500개 명사 뽑기
word_top500 =[]

#IDF를 사용해서 500개를 뽑기
#for x in range(500):
#    word_top500.append(IDFdict_sorting[x][0])
#word_top500.sort()
##print(word_top500)

#TF를 사용해서 500개를 뽑기
tf_cnt_dic = {}
#딕셔너리에 key 셋팅 value : 0
for dic_idx in range(len(IDFdict_sorting)):
    tf_cnt_dic.update( {IDFdict_sorting[dic_idx][0] : 0 } )
#파일을 읽으면서 value 카운팅
for file_idx in range(3480):
    doc_load = open('./doc_tf/doc_' + str(file_idx) + '.txt', 'r')
    #텍스트 파일 내용 읽기
    while True :
        tfWord = doc_load.readline()
        tfWord = tfWord.replace('\n', '')
        if tfWord == '':
            break
        if (tfWord in tf_cnt_dic) == True :
            cnt = tf_cnt_dic[tfWord] + 1
            tf_cnt_dic.update( { tfWord : cnt } )
    doc_load.close()
tf_cnt_dic = sorted(tf_cnt_dic.items(), key=operator.itemgetter(1), reverse=True)
#print(tf_cnt_dic)
for x in range(500):
    word_top500.append(tf_cnt_dic[x][0])
word_top500.sort()
print('500단어:')
print(word_top500)

print('DF_dic :')
print(IDFdict_sorting)
print('TF_dic : ')
print(tf_cnt_dic)

#TFIDF계산
#weight = []
for cnt in range(3480):
    TFIDF_cal(cnt, IDFdict_sorting, word_top500)
    ans_write = open('./tfidf.txt', 'a')
    ans_write.write(str(answerList[cnt]) + '\n')
    ans_write.close()

data_file.close()




###TEST DATA######
#TEST 데이터 TFIDF 계산
testFileLen = 1497

with open('Te.json', encoding='ISO-8859-1') as test_file:
    test_data = json.loads(test_file.read())

#테스트 데이터 정답 저장
test_answerList = []
for x in range(testFileLen):
    if test_data[x].get('answer') == 'tes':
        test_answerList.append(test_data[x].get('answer'))
        continue
    if test_data[x].get('answer') == 'jso':
        test_answerList.append(test_data[x].get('answer'))
        continue
    test_answerList.append(int(test_data[x].get('answer')))

#테스트파일 명사 추출

for i in range(testFileLen):
    test_NounLineList = []
    test_NounList = []
    for x in test_data[i].get('sentence'):
        # 명사들 리스트에 넣기
        if re.search('/N[a-zA-Z]+', x.encode('iso-8859-1', 'ignore').decode('euc-kr', 'ignore')):
            test_NounLineList.append(re.findall('[가-힣]+,?.?/N[a-zA-Z]+', x.encode('iso-8859-1', 'ignore').decode('euc-kr', 'ignore')))

        test_NounList = SliceNoun(test_NounLineList)


        test_f = open('./doc_tf/test/doc' + str(i) + '.txt', 'w')
        for t_data in test_NounList:
            test_f.write(t_data + '\n')
        test_f.close()


def test_TFIDF_cal(docNum, df_list, topWord_list):
    # 문서 X의 TF계산
    doc_tf = {}
    for content in topWord_list:
        doc_tf.update({content: 0})
    doc_file = open('./doc_tf/test/doc' + str(docNum) + '.txt', 'r')
    while True:
        txtWord = doc_file.readline()
        txtWord = txtWord.replace('\n', '')

        if txtWord == '':
            break
        if (txtWord in doc_tf) == True:
            val = doc_tf[txtWord] + 1
            doc_tf.update({txtWord: val})
    # print(doc_tf)

    # 문서 X의 IDF 계산
    doc_idf = {}
    for content in topWord_list:
        doc_idf.update({content: 0})
    for index in range(500):
        key = df_list[index][0]
        value = math.log(3480 / df_list[index][1], 2)
        doc_idf.update({key: value})
    # print(doc_idf)

    # 문서 X의 TFIDF 계산
    doc_tfidf = {}
    for topWord in topWord_list:
        tfidf = doc_tf[topWord] * doc_idf[topWord]
        # print(tfidf)
        doc_tfidf.update({topWord: tfidf})
    # print(doc_tfidf)

    # 문서 X의 TFIDF 정규화
    sum_tfidf = 0.0
    doc_nomal = {}
    for x in topWord_list:
        sum_tfidf += doc_tfidf[x] * doc_tfidf[x]
    sum_tfidf = math.sqrt(sum_tfidf)
    # print(sum_tfidf)
    for x in topWord_list:
        if sum_tfidf == 0:
            nomal_val = 0
        else:
            nomal_val = doc_tfidf[x] / sum_tfidf
        doc_nomal.update({x: nomal_val})
    # print(doc_nomal)

    tfidf_file = open('./tfidf_test.txt', 'a')
    for x in topWord_list:
        tfidf_file.write(str(doc_nomal[x]) + ' ')
    tfidf_file.close()

for cnt in range(testFileLen):
    test_TFIDF_cal(cnt, IDFdict_sorting, word_top500)
    test_ans_file = open('./tfidf_test.txt', 'a')
    test_ans_file.write(str(test_answerList[cnt]) + '\n')
    test_ans_file.close()
