#include<iostream>
#include<ctime>
#include<string>
#include<cstdlib>

using namespace std;

class Organism
{   private:
    
    char sym;
    int xVal;
    int yVal;
    int lifeCount;
    bool doa;
    
    public:

    Organism()//default constructor
    {
        xVal = 999;
        yVal = 999;
        lifeCount = 0;
        doa = false;
    }
    Organism(int xVal, int yVal, int orgLife)//parameter constructor
    {
        xVal = xVal;
        yVal = yVal;
        lifeCount = orgLife;
    }

    int getXVal()
    {
        return xVal;
    }
    int getYVal()
    {
        return yVal;
    }
    int getLifeCount()
    {
        return lifeCount;
    }
    bool checkAlive()
    {
        return doa;
    }

    void setXVal(int newXVal)
    {
        xVal = newXVal;
    }
    void setYVal(int newYVal)
    {
        yVal = newYVal;
    }
    void updateLifeCount(int newOrgLife)
    {
        lifeCount = newOrgLife;
    }
    void updateCheckAlive(bool newLifeStatus)
    {
        doa = newLifeStatus;
    }
    virtual char checkSym() = 0;
    virtual void printSym() = 0;
    virtual void move(){};
    virtual void breed(){};
};

class Empty: public Organism
{
    private:
    char sym;
    
    public:
    Empty():Organism(), sym('-'){}; //construcor for empty space

    void printSym() 
    {
        cout<<sym;
    }
    char checkSym()
    {
        return sym;
    } 
};

class Ant: public Organism
{
    private:
    char sym;
    
    public:
    Ant():Organism(), sym('o'){}; //constructor for ant

    void printSym() 
    {
        cout<<sym;
    }

    char checkSym()
    {
        return sym;
    }
    
    void move(Organism* objList[20][20], Empty* EmptyArr);
    void breed(Organism* objList[20][20], Ant objAnts[], int &antC);
     
};

class Doodlebug: public Organism
{
    private:
    char sym;
    int starveC;
    
    public:
    Doodlebug(): Organism(), sym('X'), starveC(0){}; //constructor for doodlebug

    void printSym() 
    {
        cout<<sym;
    }
    char checkSym()
    {
        return sym;
    }
    void updateStarveTime(int newStarveC)
    {
        starveC = newStarveC;
    }
    int checkStarveC()
    {
        return starveC;
    }
    
    void move(Organism* objList[20][20], Doodlebug objDoodles[], Empty* EmptyArr);
    void breed(Organism* objList[20][20], Doodlebug objDoodles[], int &doodleCount);
    void starve(Organism* objList[20][20], Empty* EmptyArr);
    
};

void printMatrix(Organism* objList[20][20]) //function to print the grid display
{
    for(int i = 0; i <= 19; i++)
    {
        for (int j = 0; j <= 19; j++)
        {
            objList[i][j]->printSym();
            cout<<" ";
        }
        cout<<'\n';
    }
}

void simulateOneStep(Organism* objList[20][20], Ant* antArr, Empty* EmptyArr, Doodlebug* doodlebugArr, int &antC, int &doodleCount) //perform 1 step of all series of events
{   
    int i = 0, j = 0, k = 0, l = 0, m = 0;
    while(i<400)
    {
        if(doodlebugArr[i].checkAlive() == true)
            doodlebugArr[i].move(objList, doodlebugArr, EmptyArr);
        i++;
    }

    while(j<400)
    {
        if(doodlebugArr[j].checkAlive() == true)
            doodlebugArr[j].breed(objList, doodlebugArr, doodleCount);
        j++;
    }
    
    while(k<400)
    {
        if(antArr[k].checkAlive() == true)
            antArr[k].move(objList, EmptyArr);
        k++;
    }
    
    while(l<400) 
    {
        if(antArr[l].checkAlive() == true)
            antArr[l].breed(objList, antArr, antC);
        l++;
    }
    
    while(m<400)
    {
        if(doodlebugArr[m].checkAlive() == true)
            doodlebugArr[m].starve(objList, EmptyArr);
        m++;
    }
    
    printMatrix(objList); //print updates matrix to screen
    
}

int getNextLocation(Ant* arr)
{
    int newLoc = 0;
    for(int i = 0; i < 400; i++)//search empty location for new object of type ant
    {
        if (arr[i].checkAlive() == false)
        {
            newLoc = i;
            i = 999;
        }
    }
    return newLoc;
}

int getNextLocation(Doodlebug* arr)
{
    int newLoc;
    for(int i = 0; i < 400; i++) //search empty location for new object of type doodlebug
    {
        if (arr[i].checkAlive() == false)
        {
            newLoc = i;
            i = 999;
        }
    }
    return newLoc;
}

//MAIN
int main()
{
    srand(time(NULL));
    
    int currX; 
    int currY;
    int doodleC = 0;
    int antC = 0;

    Organism* orgObjs[20][20]; //initialise all objects to null
    for(int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            orgObjs[i][j] = NULL;
        }
    }
   
    //initialise array of objects of each type
    Empty EmptyArray[400];
    Doodlebug objDoodles[400];
    Ant objAnts[400];

    for (doodleC = 0; doodleC <= 4; doodleC++) //loop to generate 5 doodlebugs randomly for initial condition
    {   
        currX = rand() % 20;
        currY = rand() % 20;
        if (orgObjs[currX][currY] == NULL)
        {
            orgObjs[currX][currY] = &objDoodles[doodleC];
            orgObjs[currX][currY]->setXVal(currX);
            orgObjs[currX][currY]->setYVal(currY);
            orgObjs[currX][currY]->updateCheckAlive(true);
        }

        else doodleC--;
    }    
    
   for (antC = 0; antC <= 99; antC++) //loop to generate 100 ants in random locations for initial condition
    {   
        currX = rand() % 20;
        currY = rand() % 20;
        if (orgObjs[currX][currY] == NULL)
        {
            orgObjs[currX][currY] = &objAnts[antC];
            orgObjs[currX][currY]->setXVal(currX);
            orgObjs[currX][currY]->setYVal(currY);
            orgObjs[currX][currY]->updateCheckAlive(true);
        }

        else antC--;
    }    
    
    for(int i = 0; i < 20; i++) //Loop to initialise empty space objects to null
    {
        for (int j = 0; j < 20; j++)
        {
            if (orgObjs[i][j] == NULL)
            {
                orgObjs[i][j] = &EmptyArray[0];
            }
        }
    }
    printMatrix(orgObjs); //print updates matrix to screen

    cout<<"Initial World Condition: 5 Doodlebugs & 100 Ants in Random Locations\n";
    
    string userInput = "";
    
    while (userInput.length() == 0)
    {   
        cout<<"Please press enter to initiate next time step: ";
        getline(cin, userInput);
        if(userInput.length() == 0)
        simulateOneStep(orgObjs, objAnts, EmptyArray, objDoodles, antC, doodleC);
    } 
    return 0;
}


void Ant::move(Organism* objList[20][20], Empty *EmptyArr)
{
    int moveDir = (rand() % 4)+1;
    updateLifeCount(getLifeCount() + 1);

    switch(moveDir)
    {
        case 1:
        if ((getXVal() - 1 >= 0) && (objList[getXVal() - 1][getYVal()]->checkSym() == '-'))
        {
            objList[getXVal() - 1][getYVal()] = objList[getXVal()][getYVal()];
            objList[getXVal()][getYVal()] = &EmptyArr[0];
            setXVal(getXVal() - 1);
        }
        break;

        case 2:
        if ((getYVal() + 1 <= 19) && (objList[getXVal()][getYVal() + 1]->checkSym() == '-'))
        {
            objList[getXVal()][getYVal() + 1] = objList[getXVal()][getYVal()];
            objList[getXVal()][getYVal()] = &EmptyArr[0];
            setYVal(getYVal() + 1);
        }
        break;

        case 3:
        if ((getXVal() + 1 <= 19) && (objList[getXVal() + 1][getYVal()]->checkSym() == '-'))
        {
            objList[getXVal() + 1][getYVal()] = objList[getXVal()][getYVal()];
            objList[getXVal()][getYVal()] = &EmptyArr[0];
            setXVal(getXVal() + 1);
        }
        break;

        case 4:
        if ((getYVal() - 1 >= 0) && (objList[getXVal()][getYVal() - 1]->checkSym() == '-'))
        {
            objList[getXVal()][getYVal() - 1] = objList[getXVal()][getYVal()];
            objList[getXVal()][getYVal()] = &EmptyArr[0];
            setYVal(getYVal() - 1);
        }
        break;

        default: break;
    }
}

void Ant::breed(Organism* objList[20][20], Ant objAnts[], int &antC)
{
    if(getLifeCount() != 0 && getLifeCount() % 3 == 0)
    {
        bool flag = false;
        int nextLoc = getNextLocation(objAnts);
        bool posUp = false, posRight = false, posDown = false, posLeft = false;
        while(flag == false && ((posUp == false) || (posRight == false) || (posDown == false) || (posLeft == false)))
        {
            int breedDir = (rand() % 4) + 1;
        
            switch(breedDir)
            {   
                case 1:
                posUp = true;
                    if ((getXVal() - 1 >= 0) && (objList[getXVal() - 1][getYVal()]->checkSym() == '-'))
                    {
                        objList[getXVal() - 1][getYVal()] = &objAnts[nextLoc];
                        objAnts[nextLoc].setXVal(getXVal() - 1);
                        objAnts[nextLoc].setYVal(getYVal());
                        objAnts[nextLoc].updateCheckAlive(true);
                        flag = true;
                    }
                    
                break;

                case 2:
                posRight = true;
                    if ((getYVal() + 1 <= 19) && (objList[getXVal()][getYVal() + 1]->checkSym() == '-'))
                    {
                        objList[getXVal()][getYVal() + 1] = &objAnts[nextLoc];
                        objAnts[nextLoc].setXVal(getXVal());
                        objAnts[nextLoc].setYVal(getYVal() + 1);
                        objAnts[nextLoc].updateCheckAlive(true);
                        flag = true;
                    }
                break;

                case 3:
                posDown = true;
                    if ((getXVal() + 1 <= 19) && (objList[getXVal() + 1][getYVal()]->checkSym() == '-'))
                    {
                        objList[getXVal() + 1][getYVal()] = &objAnts[nextLoc];
                        objAnts[nextLoc].setXVal(getXVal() + 1);
                        objAnts[nextLoc].setYVal(getYVal());
                        objAnts[nextLoc].updateCheckAlive(true);
                        flag = true;
                    }
                break;

                case 4:
                posLeft = true;
                    if ((getYVal() - 1 >= 0) && (objList[getXVal()][getYVal() - 1]->checkSym() == '-'))
                    {
                        objList[getXVal()][getYVal() - 1] = &objAnts[nextLoc];
                        objAnts[nextLoc].setXVal(getXVal());
                        objAnts[nextLoc].setYVal(getYVal() - 1);
                        objAnts[nextLoc].updateCheckAlive(true);
                        flag = true;
                    }
                break;

                default:break;

            }
        }
    }
}


void Doodlebug:: move(Organism* objList[20][20], Doodlebug objDoodles[], Empty* EmptyArr)
{
    updateLifeCount(getLifeCount() + 1);
    bool flag = false;
    bool posUp = false, posRight = false, posDown = false, posLeft = false;
    
    while(flag == false && ((posUp == false) || (posRight == false) || (posDown == false) || (posLeft == false)))
    {
        int moveDir = (rand() % 4) + 1;
        
        switch(moveDir)
        {
            case 1:
            posUp = true;
            if ((getXVal() - 1 >= 0) && (objList[getXVal() - 1][getYVal()]->checkSym() == 'o'))
            {
                objList[getXVal() - 1][getYVal()]->updateCheckAlive(false);
                objList[getXVal() - 1][getYVal()]->updateLifeCount(0);
                objList[getXVal() - 1][getYVal()] = this;
                objList[getXVal()][getYVal()] = &EmptyArr[0];
                setXVal(getXVal() - 1);
                updateStarveTime(0);
                flag = true;
            }
            break;

            case 2:
            posRight = true;
            if ((getYVal() + 1 <= 19) && (objList[getXVal()][getYVal() + 1]->checkSym() == 'o')){
                objList[getXVal()][getYVal() + 1]->updateCheckAlive(false);
                objList[getXVal()][getYVal() + 1]->updateLifeCount(0);
                objList[getXVal()][getYVal() + 1] = this;
                objList[getXVal()][getYVal()] = &EmptyArr[0];
                setYVal(getYVal() + 1);
                updateStarveTime(0);
                flag = true;
            }
            break;

            case 3:
            posDown = true;
            if ((getXVal() + 1 <= 19) && (objList[getXVal() + 1][getYVal()]->checkSym() == 'o'))
            {
                objList[getXVal() + 1][getYVal()]->updateCheckAlive(false);
                objList[getXVal() + 1][getYVal()]->updateLifeCount(0);
                objList[getXVal() + 1][getYVal()] = this;
                objList[getXVal()][getYVal()] = &EmptyArr[0];
                setXVal(getXVal() + 1);
                updateStarveTime(0);
                flag = true;
            }
            break;

            case 4:
            posLeft = true;
            if ((getYVal() - 1 >= 0) && (objList[getXVal()][getYVal() - 1]->checkSym() == 'o')){
                objList[getXVal()][getYVal() - 1]->updateCheckAlive(false);
                objList[getXVal()][getYVal() - 1]->updateLifeCount(0);
                objList[getXVal()][getYVal() - 1] = this;
                objList[getXVal()][getYVal()] = &EmptyArr[0];
                setYVal(getYVal() - 1);
                updateStarveTime(0);
                flag = true;
            }
            break;

            default: break;
        }
    }
    
    
    if(flag == false)
    {
        updateStarveTime(checkStarveC() + 1);
        int moveDir = (rand() % 4)+1;

        switch(moveDir)
        {
            case 1:
            if ((getXVal() - 1 >= 0) && (objList[getXVal() - 1][getYVal()]->checkSym() == '-'))
            {
                objList[getXVal() - 1][getYVal()] = objList[getXVal()][getYVal()];
                objList[getXVal()][getYVal()] = &EmptyArr[0];
                setXVal(getXVal() - 1);
            }
            break;

            case 2:
            if ((getYVal() + 1 <= 19) && (objList[getXVal()][getYVal() + 1]->checkSym() == '-'))
            {
                objList[getXVal()][getYVal() + 1] = objList[getXVal()][getYVal()];
                objList[getXVal()][getYVal()] = &EmptyArr[0];
                setYVal(getYVal() + 1);
            }
            break;

            case 3:
            if ((getXVal() + 1 <= 19) && (objList[getXVal() + 1][getYVal()]->checkSym() == '-'))
            {
                objList[getXVal() + 1][getYVal()] = objList[getXVal()][getYVal()];
                objList[getXVal()][getYVal()] = &EmptyArr[0];
                setXVal(getXVal() + 1);
            }
            break;

            case 4:
            if ((getYVal() - 1 >= 0) && (objList[getXVal()][getYVal() - 1]->checkSym() == '-'))
            {
                objList[getXVal()][getYVal() - 1] = objList[getXVal()][getYVal()];
                objList[getXVal()][getYVal()] = &EmptyArr[0];
                setYVal(getYVal() - 1);
            }
            break;

            default: break;
        }
        flag = true;
    }
}


void Doodlebug:: breed(Organism* objList[20][20], Doodlebug objDoodles[], int &doodleCount)
{
    if(getLifeCount() != 0 && getLifeCount() % 8 == 0)
    {
        bool flag = false;
        int nextLoc = getNextLocation(objDoodles);
        bool posUp = false, posRight = false, posDown = false, posLeft = false;
        while(flag == false && ((posUp == false) || (posRight == false) || (posDown == false) || (posLeft == false)))
        {
            int breedDir = (rand() % 4) + 1;
        
            switch(breedDir)
            {   
                case 1:
                posUp = true;
                    if ((getXVal() - 1 >= 0) && (objList[getXVal() - 1][getYVal()]->checkSym() == '-'))
                    {
                        objList[getXVal() - 1][getYVal()] = &objDoodles[nextLoc];
                        objDoodles[nextLoc].setXVal(getXVal() - 1);
                        objDoodles[nextLoc].setYVal(getYVal());
                        objDoodles[nextLoc].updateCheckAlive(true);
                        flag = true;
                    }
                break;

                case 2:
                posRight = true;
                    if ((getYVal() + 1 <= 19) && (objList[getXVal()][getYVal() + 1]->checkSym() == '-'))
                    {
                        objList[getXVal()][getYVal() + 1] = &objDoodles[nextLoc];
                        objDoodles[nextLoc].setXVal(getXVal());
                        objDoodles[nextLoc].setYVal(getYVal() + 1);
                        objDoodles[nextLoc].updateCheckAlive(true);
                        flag = true;
                    }
                break;

                case 3:
                posDown = true;
                    if ((getXVal() + 1 <= 19) && (objList[getXVal() + 1][getYVal()]->checkSym() == '-'))
                    {
                        objList[getXVal() + 1][getYVal()] = &objDoodles[nextLoc];
                        objDoodles[nextLoc].setXVal(getXVal() + 1);
                        objDoodles[nextLoc].setYVal(getYVal());
                        objDoodles[nextLoc].updateCheckAlive(true);
                        flag = true;
                    }
                break;

                case 4:
                posLeft = true;
                    if ((getYVal() - 1 >= 0) && (objList[getXVal()][getYVal() - 1]->checkSym() == '-'))
                    {
                        objList[getXVal()][getYVal() - 1] = &objDoodles[nextLoc];
                        objDoodles[nextLoc].setXVal(getXVal());
                        objDoodles[nextLoc].setYVal(getYVal() - 1);
                        objDoodles[nextLoc].updateCheckAlive(true);
                        flag = true;
                    }
                break;

                default:break;
            }
        }
    }
    return;
}


void Doodlebug::starve(Organism* objList[20][20], Empty* EmptyArr)
{
    if (checkStarveC() == 3)
    {
        updateCheckAlive(false);
        updateLifeCount(0);
        objList[getXVal()][getYVal()] = &EmptyArr[0];
    }
    return;
}


