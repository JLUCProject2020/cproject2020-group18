import pygame, sys
from pygame.locals import *
import random
import time
import pygame_textinput
import re
import os
import matplotlib.pyplot as plt
from ctypes import *
level = 0  #游戏级别
while True:
    #level=level+1
    textinput = pygame_textinput.TextInput(initial_string="Please enter your name: ",font_size=80)
    textinput2 = pygame_textinput.TextInput(initial_string="Please select game level(1~3): ", font_size=80)
    # while True:
    #     level = input('Please select game level(1~3):')
    #     level = int(level)
    #     if level >= 1 and level <= 3:
    #         break;
    #     else:
    #         print('Input Error！')

    pygame.init()

    g_ClickCount = 0
    background = pygame.image.load("./image/beijing.jpg")
    curSurface = pygame.display.set_mode((1024,768))
    pygame.display.set_caption("心理学小游戏")
    m = 2*level    #6
    W = 192        #64*3   #######################
    n = 2*level    #
    lstBlockRect = [[0 for i in range(m)] for j in range(n)]
    print(lstBlockRect)
    lstBlockFlag = [[0 for i in range(m)] for j in range(n)]
    lstIcon = []
    lstBlockFlag_over = [[1 for i in range(m)] for j in range(n)]
    print(lstBlockFlag_over)

    game_over=False

    def loadIcon(n):
        for i in range(1,int(n**2/2+1)):
            iconname = './image/'+str(i) + '.png'
            tmping = pygame.image.load(iconname)
            tmping = pygame.transform.smoothscale(tmping,(int(W/level),int(W/level)))
            lstIcon.append(tmping)
            lstIcon.append(tmping)
    loadIcon(level*2)
    random.shuffle(lstIcon)

    def generatePos():
        for i in range(m):
            for j in range(n):
                lstBlockRect[i][j] = (70+i*(W/level+30),90+j*(W/level+30),W/level,W/level)

    generatePos()

    def drawBackGround():

        curSurface.blit(background,(0,0))
        for i in range(m):
            for j in range(n):
                if lstBlockFlag[i][j] == 0:
                    pygame.draw.rect(curSurface,(166,166,166),lstBlockRect[i][j])
                else:
                    curSurface.blit(lstIcon[i*2*level+j],(70+i*(int(W/level)+30),90+j*(int(W/level)+30),int(W/level),int(W/level)))

    def drawBackGround1():

        curSurface.blit(background,(0,0))
        for i in range(m):
            for j in range(n):
                if lstBlockFlag[i][j] == 1:
                    pygame.draw.rect(curSurface,(166,166,166),lstBlockRect[i][j])
                else:
                    curSurface.blit(lstIcon[i*2*level+j],(70+i*(int(W/level)+30),90+j*(int(W/level)+30),int(W/level),int(W/level)))    #(lstIcon[i*6+j],(70+i*(W+30),90+j*(W+30),W,W))

    def findBlockByPos(mouse_x, mouse_y):
        m = 2*level    #6
        n = 2*level    #6
        for i in range(m):
            for j in range(n):
                if mouse_x > lstBlockRect[i][j][0] and mouse_x <= lstBlockRect[i][j][0] + int(W/level):
                    if mouse_y > lstBlockRect[i][j][1] and mouse_y <= lstBlockRect[i][j][1] + int(W/level):
                        print('pos',i,j)
                        return (i,j)
        print(-1,-1)
        return (-1,-1)

    def drawText(text, posx, posy, textHeight=48, fontColor=(0, 0, 0)):
        fontObj = pygame.font.Font(None, textHeight)  # 通过字体文件获得字体对象
        textSurfaceObj = fontObj.render(text, True, fontColor)  # 配置要显示的文字
        textRectObj = textSurfaceObj.get_rect()  # 获得要显示的对象的rect
        textRectObj.center = (posx, posy)  # 设置显示对象的坐标
        curSurface.blit(textSurfaceObj, textRectObj)  # 绘制字
    _input = True
    while True:
        curSurface.blit(background,(0,0))
        events = pygame.event.get()
        for event in events:
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            elif event.type == pygame.KEYUP:
                if event.key == 13:
                    level=int(textinput2.get_text().split(": ")[1]+'\t')
                    m = 2 * level  # 6
                    W = 192  # 64*3   #######################
                    n = 2 * level  #
                    lstBlockRect = [[0 for i in range(m)] for j in range(n)]
                    print(lstBlockRect)
                    lstBlockFlag = [[0 for i in range(m)] for j in range(n)]
                    lstIcon = []
                    lstBlockFlag_over = [[1 for i in range(m)] for j in range(n)]
                    print(lstBlockFlag_over)
                    loadIcon(level * 2)
                    random.shuffle(lstIcon)
                    generatePos()
                    _input = False
    
        if textinput2.update(events):
            print(textinput2.get_text())
        curSurface.blit(textinput2.get_surface(),(0,0))
        pygame.display.update()
        if _input == False:
            break
    _input = True
    while True:
        curSurface.blit(background, (0, 0))
        events = pygame.event.get()
        for event in events:
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            elif event.type == pygame.KEYUP:
                if event.key == 13:
                    name=textinput.get_text().split(": ")[1]+'\t'
                    _input = False
        for event in events:
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            elif event.type == pygame.KEYUP:
                if event.key == 13:
                    name = textinput.get_text().split(": ")[1] + '\t'
                    _input = False

        if textinput.update(events):
            print(textinput.get_text())
        curSurface.blit(textinput.get_surface(), (0, 0))
        pygame.display.update()
        if _input == False:
            break
    _time = 3*level+4      #10,   让用户记忆图片的时间，随着难度level的加大，记忆的时间增长
    COUNT=pygame.USEREVENT+1
    pygame.time.set_timer(COUNT,1000)
    while True:
        # ~ _time -= 1
        drawBackGround1()
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            elif event.type==COUNT:
                _time -= 1
        drawText("You have "+str(_time)+" seconds",800,100)
        drawText("to remember!!!",800,150)
        #clock.tick(1000)
        pygame.display.update()
        # ~ time.sleep(1)
        
        if _time == 0:
            break
    
    start=time.clock()
    while True:
        mouse_x,mouse_y = -1,-1
        drawBackGround()
        # drawIcon()
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            elif event.type == MOUSEBUTTONDOWN:
                mouse_x,mouse_y = event.pos
                curIcon = findBlockByPos(mouse_x,mouse_y)
                if curIcon != (-1,-1) and lstBlockFlag != lstBlockFlag_over:
                    g_ClickCount += 1
                    print(g_ClickCount)
                    lstBlockFlag[curIcon[0]][curIcon[1]] = 1
                    index_icon = curIcon[0]*n+curIcon[1]
                    if g_ClickCount % 2 == 1:
                        first_ClickIcon = [lstIcon[index_icon],curIcon]
                        print(first_ClickIcon)
                    else:
                        second_ClickIcon = [lstIcon[index_icon],curIcon]
                        print(second_ClickIcon)
                        if second_ClickIcon[0] != first_ClickIcon[0] or second_ClickIcon[1] == first_ClickIcon[1]:
                            pygame.time.wait(300)
                            lastIcon = first_ClickIcon[1]
                            thisIcon = second_ClickIcon[1]
                            lstBlockFlag[lastIcon[0]][lastIcon[1]] = 0
                            lstBlockFlag[thisIcon[0]][thisIcon[1]] = 0
                            print("Mismatch")
                            print(lstBlockFlag)
        if lstBlockFlag == lstBlockFlag_over:
            drawBackGround()
            #pygame.display.update()
            game_over=True
        if game_over:
            pygame.display.update()
            break
        elif lstBlockFlag != lstBlockFlag_over:
            pygame.display.update()
    end=time.clock()
    print(end-start)
    file_object = open("./rank.txt","a+")
    row=name+'\t'+str(format(end-start,'.2f'))+'\t'+str(g_ClickCount)+'\t'+str(level)+'\n'
    #row = name + '\t' + str(end - start) + '\t' + str(g_ClickCount) + '\t' + str(level) + '\n'
    print(row)
    file_object.write(row)
    file_object.close()
    file_object = open("./last_user.txt","w")
    file_object.write(row)
    file_object.close()
    pname="guojy.exe"
    if os.path.exists(pname):
        f=os.popen(pname)
        data=f.readlines()
        f.close()
        print (data)
    os.system(pname)
    drawText("You have "+str(g_ClickCount)+" mouse",800,50)    #150
    drawText("clicks in "+str(format(end-start,'.2f'))+'s!',800,100)     #200
    drawText("Rank by clicks",800,150,textHeight=48,fontColor=(237,145,33))
    with open("./rank_clicks.txt","r") as file_object:
        lines=file_object.readlines()
        i=1
        temp=150      #300
        for line in lines:
            i=i+1
            temp+=50
            line=re.sub('\s','',line)
            drawText(line, 800, temp, textHeight=40)
            #if i>3:          #只显示前3名
                #break
    temp=temp+50
    drawText("Rank by time", 800, temp,textHeight=48,fontColor=(237,145,33))
    with open("./rank_time.txt","r") as file_object:
        lines=file_object.readlines()
        i=1
        for line in lines:
            i=i+1
            temp+=50
            line=re.sub('\s','',line)
            drawText(line, 800, temp, textHeight=40)
            #if i>3:          #只显示前3名
                #break
    drawText("Please press enter to replay", 800, 700, textHeight=48, fontColor=(237, 145, 33))
    Time = []
    Clicks = []
    with open("./time_score.txt", "r") as fp1:
        for line in fp1.readlines():
            line = line.strip('\n')
            Time.append(float(line))
    with open("./clicks_score.txt", "r") as fp2:
        for line in fp2.readlines():
            line = line.strip('\n')
            Clicks.append(int(line))
    t = list(range(len(Time)))
    plt.plot(t, Time, label='时间',color='g')
    # plt.plot(t, Clicks, label='点击次数')
    plt.title('游戏成绩趋势图', fontproperties='simhei', fontsize=24)
    plt.xlabel('次数', fontproperties='simhei', fontsize=18)
    plt.ylabel('游戏用时（秒)', fontproperties='simhei', fontsize=18)
    plt.show()
    t = list(range(len(Clicks)))
    plt.plot(t, Clicks, label='点击次数',color='r')
    # plt.plot(t, Clicks, label='点击次数')
    plt.title('游戏成绩趋势图', fontproperties='simhei', fontsize=24)
    plt.xlabel('次数', fontproperties='simhei', fontsize=18)
    plt.ylabel('点击次数', fontproperties='simhei', fontsize=18)
    plt.show()
    while True:
        backOne=False
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            elif event.type == pygame.KEYUP:
                if event.key == 13:
                    backOne=True
        if backOne:
            break
        pygame.display.update()
