class Tokenizer:

    def __init__(self):
        pass

    def tokenizeFile(self,fname):
        tokenizedLines = []
        with open(fname) as f:
            for line in f:
                line = line.strip()
                tokenizedLines.append(line.split(' '))
        return tokenizedLines


class Pass1:

    def __init__(self, fname):
        self.mnt = []
        self.mdt = []
        self.kpdt = []
        self.kpdtPtr = 1
        self.mdtPtr = 1
        self.fname = fname
        pass

    def processMacro(self, instructions):

        pnt = []
        
        # PROCESS MNT ENTRY
        mntEntry = ""
        mntEntry += instructions[1][0] + " "
        ppCount = 0
        kpCount = 0
        for i in instructions[1]:
            if '=' not in i : 
                ppCount += 1
            else :
                kpCount += 1
        ppCount -= 1
        mntEntry += str(ppCount) + " "
        mntEntry += str(kpCount) + " "
        mntEntry += str(self.kpdtPtr) + " "
        mntEntry += str(self.mdtPtr) + " "
        self.mnt.append(mntEntry)


        # PROCESS KPDT ENTRY
        for i in instructions[1]:
            if '=' in i:
                kptEntry = ""
                name = i[0:i.index('=')]
                val = i[i.index('=')+1:]
                if val:
                    kptEntry += name + " " + str(val)
                else:
                    kptEntry += name + " " + str(-1)
                self.kpdt.append(kptEntry)
                self.kpdtPtr += 1
        

        # PROCESS PNT ENTRY
        for i in instructions[1]:
            if '=' not in i and '&' in i:
                name = i[i.index('&'):]
                pnt.append(name)
        for i in instructions[1]:
            if '=' in i:
                name = i[0:i.index('=')]
                pnt.append(name)


        # PROCESS MDT ENTRY
        for i in instructions[2:]:
            mdtEntry = ""
            for j in i: 
                if('&' in j):
                    mdtEntry += "(P," + str(pnt.index(j)+1) + ") "
                else:
                    mdtEntry += j + " "
            self.mdt.append(mdtEntry)
            self.mdtPtr += 1

    def performPass1(self):
        
        tknz = Tokenizer()
        instructions = tknz.tokenizeFile(self.fname)
        
        while ['MACRO'] in instructions:
            start = instructions.index(['MACRO'])
            end = instructions.index(['MEND'])
            temp = instructions[start:end+1]
            instructions = instructions[end+1:]
            self.processMacro(temp)

        with open('mnt.txt', 'w+') as f:
            for i in self.mnt:
                f.write(i)
                f.write('\n')

        with open('mdt.txt', 'w+') as f:
            for i in self.mdt:
                f.write(i)
                f.write('\n')

        with open('kpdt.txt', 'w+') as f:
            for i in self.kpdt:
                f.write(i)
                f.write('\n')


def main():
    pass1 = Pass1('tc1.txt')
    pass1.performPass1()


if __name__=="__main__":
    main()