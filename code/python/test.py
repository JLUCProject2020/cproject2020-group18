import os
import numpy as np
import matplotlib.pyplot as plt
while True:
    level = input('Please select game level(1~3):')
    level = int(level)
    if level>=1 and level<=3:
        break;
    else:
        print('Input Error！')
Time=[]
Clicks=[]
with open("./time_score.txt", "r") as fp:
    for line in fp.readlines():
        line=line.strip('\n')
        Time.append(float(line))
with open("./clicks_score.txt", "r") as fp:
    for line in fp.readlines():
        line=line.strip('\n')
        Clicks.append(int(line))
t = list(range(len(Time)))
plt.plot(t,Time,label='时间')
#plt.plot(t, Clicks, label='点击次数')
plt.title('游戏成绩趋势图', fontproperties='simhei', fontsize=24)
plt.xlabel('次数', fontproperties='simhei', fontsize=18)
plt.ylabel('游戏用时（秒)', fontproperties='simhei', fontsize=18)
plt.show()
t=list(range(len(Clicks)))
plt.plot(t,Clicks,label='点击次数')
#plt.plot(t, Clicks, label='点击次数')
plt.title('游戏成绩趋势图', fontproperties='simhei', fontsize=24)
plt.xlabel('次数', fontproperties='simhei', fontsize=18)
plt.ylabel('点击次数', fontproperties='simhei', fontsize=18)
plt.show()


