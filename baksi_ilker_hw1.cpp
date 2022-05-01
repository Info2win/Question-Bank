// 01001001 01010100 01010111
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <random>
#include "LinkedList.h"
#define TOPIC_COUNT 5
#define FILE_NAME "Hw1TextFile.txt"
#define END_POINT "#"

using namespace std;

class myQuestion
{
private:
    int no; // question number
    string question; // question itself
    string answer; // question's answer in T/F format
public:
    myQuestion(){}
    myQuestion(const myQuestion &c) // COPY CONSTUCTOR
    {
        this->no = c.no;
        this->question = c.question;
        this->answer = c.answer;
    }
    // SET FUNCTIONS
    void setNo(int no){this->no = no;}
    void setQuestion (string question){this->question = question;}
    void setAnswer (string answer) {this->answer = answer;}
    // GET FUNCTIONS
    int getNo () {return no;}
    string getQuestion () {return question;}
    string getAnswer () {return answer;}
    // OVERLOADED OPERATORS
    friend ostream& operator << (ostream &myOut, myQuestion &data); // outputs question and its answer
    friend bool operator == (const myQuestion &left, const myQuestion &right);// compares no
    myQuestion& operator = (const myQuestion &right);

};
myQuestion& myQuestion::operator=(const  myQuestion &right)
{
    this->no = right.no;
    this->question = right.question;
    this->answer = right.answer;
    return *this;
}
bool operator==(const myQuestion &left,const myQuestion &right)
    {
        if((left.no== right.no))return 1;
        else return 0;
    }
ostream& operator << (ostream &myOut, myQuestion &data)
    {
        string correctAnswer;
        if(data.answer== "T") correctAnswer = "True";
        if(data.answer== "F") correctAnswer = "False";
        cout<<data.question<<" Correct Answer:"<<correctAnswer<<endl;
        return myOut;
    }
class myElement
{
private:
    string topic;// Linked List,Stack,Queue,Binary Tree and Sorting
    LinkedList<myQuestion> questions;// THE LINKED LIST COANTAINING QUESTIONS' DATA (no,question and answer)
public:
    myElement(){}
    myElement(const myElement &c) // COPY CONSTUCTOR
    {
        this->topic = c.topic;
        this->questions = c.questions;
    }
    // SET FUNCTIONS
    void setTopic (string topic) {this->topic = topic;}
    void setQuestions (LinkedList<myQuestion> questions) {this->questions = questions;}
    // GET FUNCTIONS
    string getTopic () {return topic;}
    LinkedList<myQuestion>& getMyQuestions () {return questions;}

};

void takeQuestions(myQuestion &tempQuestion,myElement questionBank[],string &tempString) // takes questions, their numbers and answers from a file
{
ifstream infile (FILE_NAME); // open a file to read topic names, questions and its answers
    if(infile.is_open()) // is file opened properly ?
    {
        int topicNo=0; // index of the topic in the questionBank array
        int questionNo =0; // questions' numbers (reset to 0 for every topic)
      while(!infile.eof()) // did we reach end of file ?
      {
            getline(infile,tempString);
            if(tempString.length()>0) // check if the line is empty
                {
                    questionBank[topicNo].setTopic(tempString); // fill the topic
                    while(1) // infinite loop
                    {
                        getline(infile,tempString);
                        if(tempString == END_POINT) // check if it is end of the topic
                        {
                            questionNo = 0; // reset questions' numbers
                            topicNo++; // next topic
                            break; // exit the loop
                        }
                        tempQuestion.setQuestion(tempString); // SET THE QUESTION
                        getline(infile,tempString);
                        tempQuestion.setAnswer(tempString);// SET THE ANSWER
                        questionNo++;
                        tempQuestion.setNo(questionNo); // SET THE NO
                        questionBank[topicNo].getMyQuestions().insertLast(tempQuestion); // INSERT THE QUESTION
                    }
                }






      }
      infile.close(); // All the inputs are taken, so closing the file

    }
    else
    cerr<< "The File"<<FILE_NAME<< "could not opened properly!";
}
void generateRandomIntegers(int &r1, int &r2) // creates random integers which are not same
{
        mt19937 rng (time(0));
        uniform_int_distribution<> random(1,5);
        r1 = random(rng);
        r2 = random(rng);
        while(r1 == r2) // r1 and r2 should be different, so we do not ask the same question again
        {
           r2 = random(rng);
        }
}
void takeAnswer(string &answer) // inputs end-user's answers for questions & handles errors
{
    while(!(answer =="T"||answer =="F"||answer =="t"||answer =="f"))
        {
        try
        {


            cin>>answer;
            if(answer == "t") throw (1);
            if(answer == "f")throw(1.5);
            if(!(answer =="T"||answer =="F"||answer =="t"||answer =="f"))throw("You've entered unvalidated answer. Enter 'T' or 't' for True. Enter 'F' or 'f' for False.");

        }
        catch(int err)
        {
            answer = "T";
        }
        catch (double err)
        {
            answer = "F";
        }
        catch (char const* err)
        {
            cerr<<err<<endl;
        }
        }

}
int main()
{
    // VARIABLES SECTION
    myQuestion tempQuestion; // temporary Question to insert questions into the LL
    myElement questionBank[TOPIC_COUNT]; // THE QUESTIONBANK CONTAINING THE TOPICS & THE LINKED LIST
    string tempString; // temporary string
    int questionNumber=0; // holds asked questions' count
    LinkedList<myQuestion> wrongQuestions; // holds questions got wrong by end-user
    // INPUT SECTION
    takeQuestions(tempQuestion,questionBank,tempString);
    // OUTPUT SECTION
    cout<<"Data Structures Quiz"<<endl<<"Answer the following:"<<endl;
    for(int i=0; i<TOPIC_COUNT;i++)
    {
        // LOCAL VARIABLES SECTION
        int r1,r2; // holds random number integers
        myQuestion q1,q2; // temporary variables to search questions to be asked
        string answer; // holds end-user's answers to questions
        // TEST THE END-USER SECTION
        generateRandomIntegers(r1,r2);
        q1.setNo(r1);
        q2.setNo(r2);
        q1 = questionBank[i].getMyQuestions().search(q1)->data; // find the question with no:r1
        q2 = questionBank[i].getMyQuestions().search(q2)->data; // find the question with no:r2
        cout<< questionBank[i].getTopic()<<" Questions"<<endl;
        cout<< " "<<questionNumber+1<<"."<<" "<<q1.getQuestion()<<"(T/F):";
        takeAnswer(answer);
        if(answer != q1.getAnswer())
        {
            wrongQuestions.insertLast(q1);
        }
        questionNumber++;
        cout<< " "<<questionNumber+1<<"."<<" "<<q2.getQuestion()<<"(T/F):";
        answer = "a"; // make answer !(T/t/F/f), so program enters to the loop in the takeAnswer function
        takeAnswer(answer);
        if(answer != q2.getAnswer())
        {

            wrongQuestions.insertLast(q2);
        }
        questionNumber++;

    }
    // OUTPUT THE RESULT OF THE END-USER
    cout<< "Your score:"<< (questionNumber-wrongQuestions.length())<<"/"<<questionNumber<<endl<<"Incorrectly answered questions:"<<endl<<wrongQuestions;
    return 0;
}
