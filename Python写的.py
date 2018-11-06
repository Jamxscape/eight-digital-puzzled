import numpy as np

class State:
    def __init__(self, state, directionFlag=None, parent=None):# directionFlag为记录移动何方向，parent为上一次移动方向的为何
        self.state = state
        # 创建当前状态的Open表
        self.direction = ['up', 'down', 'right', 'left']# 定义移动方向
        if directionFlag:
            self.direction.remove(directionFlag)
       # 记录可能出现的移动方向
        self.parent = parent
        self.symbol = ' '

    def getDirection(self):# 获取当前方向
        return self.direction

    def showInfo(self):# 打印棋盘
        for i in range(3):
            for j in range(3):
                print(self.state[i, j], end='  ')
            print("\n")
        print('->')
        return

    def getEmptyPos(self):# 获取空格的位置
        postion = np.where(self.state == self.symbol)
        return postion

    def generateSubStates(self):# 移动后的棋盘，子棋盘
        if not self.direction:
            return []
        subStates = []
        boarder = len(self.state) - 1
        # x ,y 的最大值
        row, col = self.getEmptyPos()
        if 'left' in self.direction and col > 0:
        # 左移棋子
            s = self.state.copy() #缓存当前棋子的位置
            temp = s.copy()  # 棋子位置的备份，已准备再次调用
            s[row, col] = s[row, col-1]
            s[row, col-1] = temp[row, col]
            news = State(s, directionFlag='right', parent=self)
            subStates.append(news)
        if 'up' in self.direction and row > 0:
        # 向上移动棋子
            s = self.state.copy()
            temp = s.copy()
            s[row, col] = s[row-1, col]
            s[row-1, col] = temp[row, col]
            news = State(s, directionFlag='down', parent=self)
            subStates.append(news)
        if 'down' in self.direction and row < boarder:
            # 向下移动棋子
            s = self.state.copy()
            temp = s.copy()
            s[row, col] = s[row+1, col]
            s[row+1, col] = temp[row, col]
            news = State(s, directionFlag='up', parent=self)
            subStates.append(news)
        if self.direction.count('right') and col < boarder:
            # 向右移动棋子
            s = self.state.copy()
            temp = s.copy()
            s[row, col] = s[row, col+1]
            s[row, col+1] = temp[row, col]
            news = State(s, directionFlag='left', parent=self)
            subStates.append(news)
        return subStates#将移动的棋子返回

    def solve(self):
        # 生成空的open表
        openTable = []
       # 生成空的close表
        closeTable = []
        # 附加原来状态到open表
        openTable.append(self)
        steps = 1
        # start the loop
        while len(openTable) > 0:
            n = openTable.pop(0)
            closeTable.append(n)
            subStates = n.generateSubStates()
            path = []
            for s in subStates:
                if (s.state == s.answer).all():
                    while s.parent and s.parent != originState:
                        path.append(s.parent)
                        s = s.parent
                    path.reverse()
                    return path, steps+1
            openTable.extend(subStates)
            steps += 1
        else:
            return None, None

if __name__ == '__main__':
    # the symbol representing the empty place
    # you can change the symbol at here
    symbolOfEmpty = ' '

    State.symbol = symbolOfEmpty
    # set the origin state of the puzzle
    originState = State(np.array([[2,symbolOfEmpty,3], [1, 8, 4], [7, 6, 5]]))
    # and set the right answer in terms of the origin
    State.answer = np.array([[2,3,State.symbol], [1, 8, 4], [7, 6, 5]])
    s1 = State(state=originState.state)
    path, steps = s1.solve()
    if path:    # if find the solution
        for node in path:
                # print the path from the origin to final state
                node.showInfo()
        print(State.answer)
        print("Total steps is %d" % steps)