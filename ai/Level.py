
class Level():
    def __init__(self):
        self.getLevel = {1: [],
                    2: ["linemate"],
                    3: ["linemate", "deraumere", "sibur"],
                    4: ["linemate", "linemate", "phiras", "phiras", "sibur"],
                    5: ["linemate", "deraumere", "sibur", "sibur", "sibur", "phiras"],
                    6: ["linemate", "deraumere", "deraumere", "sibur", "mendiane", "mendiane", "mendiane"],
                    7: ["linemate", "deraumere", "deraumere", "sibur", "sibur", "sibur", "phiras"],
                    8: ["linemate", "linemate", "deraumere", "deraumere", "sibur", "sibur", "mendiane", "mendiane",  "phiras",  "phiras", "thystame"]}
        self.matesNeeded = {1: 1, 2: 1, 3: 2, 4: 2, 5: 4, 6: 4, 7: 6, 8: 6}

    def checkIfCanLevelUp(self, inventory, level, file):
        tohave = {}
        for i in self.getLevel[level]:
            if i in tohave:
                tohave[i] += 1
            else:
                tohave[i] = 1
        for i in tohave:
            if i not in inventory or inventory[i] < tohave[i]:
                return False
        return True