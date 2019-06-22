#include <iostream>
#include <string>
#include <array>
#include <fstream>
#include <iomanip>

using namespace std;

//********************************************
//********************************************
//********************************************
//Class: single linked list of process nodes


class PROCESS_NODE
{
public:
	int ProcessNum;
	int CPU[20]; //data element
	int IO[20];
	int WaitTime;
	int IOtime;
	int CPUtime;
	int RT;
	int ResponseTime;
	PROCESS_NODE *next; //pointer element
};

class PROCESS_LIST_CLASS
{
public:
	PROCESS_LIST_CLASS();//default constructor
	PROCESS_LIST_CLASS::~PROCESS_LIST_CLASS();
	void Insert(int vProcessNum, int vCPU[], int vIO[], int vWaitTime, int vIOtime, int vCPUtime, int vRT, int vResponseTime );
	void InsertSort(int vProcessNum, int vCPU[], int vIO[],int vWaitTime, int vIOtime, int vCPUtime, int vRT, int vResponseTime);
	void Remove();
	void Remove(PROCESS_NODE *p);
	void Print();

	PROCESS_NODE *front, *back;

};

//Default Contructor
PROCESS_LIST_CLASS::PROCESS_LIST_CLASS()
{
	//cout << "Inside the default constructor\n";
	front = back = 0;

}



//Destructor
PROCESS_LIST_CLASS::~PROCESS_LIST_CLASS()
{
	//cout << "Destructor has been called\n";
	while (front != 0)
	{
		PROCESS_NODE *p = front;
		front = front->next;
		delete p;
	}
}



//Insert Node at back of list
void PROCESS_LIST_CLASS::Insert(int vProcessNum, int vCPU[], int vIO[], int vWaitTime, int vIOtime, int vCPUtime, int vRT, int vResponseTime)
{
	if (front == 0)
	{
		front = new PROCESS_NODE;
		front->ProcessNum = vProcessNum;

		int i = 0;
		while (i <= 19)
		{
			front->CPU[i] = vCPU[i];
			i++;
		}
		
		
		i = 0;
		while (i <= 19)
		{
			front->IO[i] = vIO[i];
			i++;
		}
		

		front->WaitTime = vWaitTime;
		front->IOtime = vIOtime;
		front->CPUtime = vCPUtime;
		front->RT = vRT;
		front->ResponseTime = vResponseTime;

		front->next = 0;
		back = front;
	}

	else
	{
		PROCESS_NODE *p = new PROCESS_NODE;

		p->ProcessNum = vProcessNum;

		int i = 0;
		while (i <= 19)
		{
			p->CPU[i] = vCPU[i];
			i++;
		}

		i = 0;
		while (i <= 19)
		{
			p->IO[i] = vIO[i];
			i++;
		}

		p->WaitTime = vWaitTime;
		p->IOtime = vIOtime;
		p->CPUtime = vCPUtime;
		p->RT = vRT;
		p->ResponseTime = vResponseTime;

		p->next = 0;
		back->next = p;
		back = back->next;
	}
}


void PROCESS_LIST_CLASS::InsertSort(int vProcessNum, int vCPU[], int vIO[], int vWaitTime, int vIOtime, int vCPUtime, int vRT, int vResponseTime)
{

	PROCESS_NODE *p = new PROCESS_NODE;
	p->ProcessNum = vProcessNum;

	int i = 0;
	while (i <= 19)
	{
		p->CPU[i] = vCPU[i];
		i++;
	}


	i = 0;
	while (i <= 19)
	{
		p->IO[i] = vIO[i];
		i++;
	}


	p->WaitTime = vWaitTime;
	p->IOtime = vIOtime;
	p->CPUtime = vCPUtime;
	p->RT = vRT;
	p->ResponseTime = vResponseTime;
	p->next = 0;



	if (front == 0)
	{
		front = back = p;
	}
	else if (vProcessNum < front->ProcessNum)
	{
		p->next = front;
		front = p;
	}
	else if (vProcessNum > back->ProcessNum)
	{
		back->next = p;
		back = p;
	}
	else
	{
		PROCESS_NODE *curr, *prev;
		curr = prev = front;

		while (curr != 0 && vProcessNum > curr->ProcessNum)
		{
			prev = curr;
			curr = curr->next;
		}
		p->next = curr;
		prev->next = p;
	}
}


//Removes process from front of list
void PROCESS_LIST_CLASS::Remove()
{
	if (front != 0)
	{
		PROCESS_NODE *p = front;
		front = front->next;
		delete p;
	}
	else
	{
		cout << "ERROR: List Empty\n";
		"ERROR: List Empty\n";
	}
}


//Removes the process at pointer p
void PROCESS_LIST_CLASS::Remove(PROCESS_NODE *p)
{
	if (p == front && front == back)
	{
		delete p;
		front = back = 0;
	}
	else if (p == front)
	{
		front = front->next;
		delete p;
	}
	else
	{
		PROCESS_NODE *backptr = front;
		while (backptr != 0 && backptr->next != p)
		{
			backptr = backptr->next;
		}
		if (p == back)
		{
			back = backptr;
		}
		backptr->next = p->next;
		delete p;
	}
}


void PROCESS_LIST_CLASS::Print()
{
	 
	if (front == 0)
	{
		cout << "List Empty\n";
	}
	
	PROCESS_NODE *p = front;

	while (p != 0)
	{
		cout << "Process " << p->ProcessNum << endl;

		int i = 0;
		while (p->CPU[i] != -1)
		{
			cout << p->CPU[i] << " ";
			i++;
		}
		cout << endl;

		i = 0;
		while (p->IO[i] != -1)
		{
			cout << p->IO[i] << " ";
			i++;
		}
		cout << endl;
		
		//cout << p->CPU[0] << " " << p->CPU[1] << " " << p->CPU[2] << " " << p->CPU[3] << " " << p->CPU[4] << " " << p->CPU[5] << " " << p->CPU[6] << " " << p->CPU[7] << endl;

		cout << "Wait Time: " << p->WaitTime << endl;
		cout << "IO Time: " << p->IOtime << endl;
		cout << "CPU Time: " << p->CPUtime << endl;

		p = p->next;

		cout << endl << endl;
		
	}
}

//********************************************
//********************************************
//********************************************



//The program is a FCFS simulation using a singly linked list of process nodes.
//All porcesses inputed into ready queue. When the processor is free the first node from ready queue is
//moved to executing. When it is finished in executing it moves to IO/ WHen its current IO time has expired,
//it moves back to the end of the ready queue.
int main ()
{
	PROCESS_LIST_CLASS Ready;
	PROCESS_LIST_CLASS IO;
	PROCESS_LIST_CLASS Executing;
	PROCESS_LIST_CLASS COMPLETE;

	ofstream outputfile;
	outputfile.open("FCFSoutput.txt");

	int i = 0;
	int ContextSwitch = 0;
	int CurrentTime = 0;

	//Input data, builds the ready queue
	int A1[20] = { 12, 10, 15, 11, 9, 10, 11, -1};
	int B1[20] = { 44, 52, 21, 42, 31, 77, -1};
	Ready.Insert(1, A1, B1, 0, 0, 0, 1, 0);


	int A2[20] = { 18, 17, 16, 7, 17, 11, 12, 14, -1 };
	int B2[20] = { 32, 42, 27, 41, 33, 43, 32, -1 };
	Ready.Insert(2, A2, B2, 0, 0, 0, 1, 0);
	
	int A3[20] = { 21, 15, 5, 9, 11, 14, 8, -1 };
	int B3[20] = { 24, 27, 28, 26, 49, 55, -1 };
	Ready.Insert(3, A3, B3, 0, 0, 0, 1, 0);

	int A4[20] = { 5, 4, 6, 8, 4, 3, 6, 5, -1 };
	int B4[20] = { 35, 41, 45, 51, 61, 54, 61, -1 };
	Ready.Insert(4, A4, B4, 0, 0, 0, 1, 0);

	int A5[20] = { 4, 6, 5, 4, 5, 14, 7, 12, 15, -1 };
	int B5[20] = { 41, 26, 38, 33, 37, 28, 18, 33, -1 };
	Ready.Insert(5, A5, B5, 0, 0, 0, 1, 0);

	int A6[20] = { 7, 5, 6, 5, 4, 7, 6, 5, -1 };
	int B6[20] = { 33, 31, 32, 41, 42, 39, 33, -1 };
	Ready.Insert(6, A6, B6, 0, 0, 0, 1,0);

	int A7[20] = { 22, 7, 5, 24, 4, 3, 6, 6, 5, -1 };
	int B7[20] = { 38, 41, 29, 26, 32, 22, 26, 36, -1 };
	Ready.Insert(7, A7, B7, 0, 0, 0, 1, 0);

	int A8[20] = { 25, 20, 16, 7, 14, 15, 4, 3, 5, 4, -1 };
	int B8[20] = { 21, 33, 41, 21, 23, 31, 32, 32, 41, -1 };
	Ready.Insert(8, A8, B8, 0, 0, 0, 1, 0);

	int A9[20] = { 3, 14, 8, 4, 7, 5, 4, 5, 16, -1 };
	int B9[20] = { 37, 41, 30, 19, 33, 18, 26, 31, -1 };
	Ready.Insert(9, A9, B9, 0, 0, 0, 1, 0);
	


	//while loop, processes continue moving and current time increasing until all three lists
	//(executing, ready and IO) are empty and all processes are complete
		while (Executing.front != 0 || Ready.front != 0 || IO.front != 0)
		{

			//******If process in executing is finished, move process to IO list**********
			if (Executing.front != 0 && Executing.front->CPU[0] == 0)
			{
				//Copies CPU array from front node of executing into array c minue the zero value leading the CPU array
				int c[20] = { 0 };
				i = 0;
				while (Executing.front->CPU[i] != -1)
				{
					c[i] = Executing.front->CPU[i + 1];
					i++;
				}

				//Copies IO array from front node of executing into array d
				int d[20] = { 0 };
				i = 0;
				while (Executing.front->IO[i] != -1)
				{
					d[i] = Executing.front->IO[i];
					i++;
				}
				d[i] = -1;

				//If all CPU bursts have been completed for this process, moves to COMPLETE list. Otherwise, back to IO
				if (c[0] == -1)
				{
					COMPLETE.InsertSort(Executing.front->ProcessNum, c, d, Executing.front->WaitTime, Executing.front->IOtime,
						Executing.front->CPUtime, Executing.front->RT, Executing.front->ResponseTime);
				}
				else
				{
					IO.InsertSort(Executing.front->ProcessNum, c, d, Executing.front->WaitTime, Executing.front->IOtime,
						Executing.front->CPUtime, Executing.front->RT, Executing.front->ResponseTime);
				}

				Executing.Remove();
				ContextSwitch = 1;

			}
			//***************************************************************************



			//****************Checks for IO completion, returns process to back of queue*****************

			PROCESS_NODE *p = IO.front;

			while (p != 0)
			{
				//if the IO is complete for a process, process moved to ready queue
				if (p->IO[0] == 0)
				{
					//Copies CPU array from p node of IO into array c
					int c[20] = { 0 };
					i = 0;
					while (p->CPU[i] != -1)
					{
						c[i] = p->CPU[i];
						i++;
					}
					c[i] = -1;


					//Copies IO array from p node of IO list into array d, removes first array (zero)
					int d[20] = { 0 };
					i = 0;
					while (p->IO[i] != -1)
					{
						d[i] = p->IO[i + 1];
						i++;
					}


					Ready.Insert(p->ProcessNum, c, d, p->WaitTime, p->IOtime, p->CPUtime, p->RT, p->ResponseTime);

					IO.Remove(p);


					if (IO.front == 0)
					{
						p = 0;
					}
					else
					{
						p = IO.front;
					}
				}
				else
				{
					p = p->next;
				}
			}

			//**********************************************************


			//*****If the processor is empty, moves first node in ready to executing list*****

			if (Executing.front == 0 && Ready.front != 0)
			{

				//Copies CPU aarray from front node of ready into array c
				int c[20] = { 0 };
				i = 0;
				while (Ready.front->CPU[i] != -1)
				{
					c[i] = Ready.front->CPU[i];
					i++;
				}
				c[i] = -1;

				//Copies IO array from front node of ready into array d
				int d[20] = { 0 };
				i = 0;
				while (Ready.front->IO[i] != -1)
				{
					d[i] = Ready.front->IO[i];
					i++;
				}
				d[i] = -1;

				//Insert front of ready list into executing list
				Executing.Insert(Ready.front->ProcessNum, c, d, Ready.front->WaitTime, Ready.front->IOtime,
					Ready.front->CPUtime, Ready.front->RT, Ready.front->ResponseTime);

				Ready.Remove();
				ContextSwitch = 1;
				Executing.front->RT = 0;
			}
			//**************************************************



			//*************decrements cpu burst in processor (executing list) and increases process' CPUtime************
			if (Executing.front != 0)
			{
				Executing.front->CPU[0] = Executing.front->CPU[0] - 1;
				Executing.front->CPUtime = Executing.front->CPUtime + 1;
			}



			//*****************increments waiting time and ResponseTime (if not been on processor) in ready queue*******
			if (Ready.front != 0)
			{
				PROCESS_NODE *p = Ready.front;

				while (p != 0)
				{
					p->WaitTime = p->WaitTime + 1;

					if (p->RT == 1)
					{
						p->ResponseTime = p->ResponseTime + 1;
					}

					p = p->next;
				}
			}


			//*******************display info at context switch***********************************
			if (ContextSwitch == 1)
			{
				cout   << "Current Time:" << setw(2) << CurrentTime << endl << endl;
				outputfile << "Current Time:" << setw(2) << CurrentTime << endl << endl;

				//prints executing
				if (Executing.front != 0)
				{
					cout << "Now running:" << setw(3) << "P" << Executing.front->ProcessNum << endl;
					outputfile << "Now running:" << setw(3) << "P" << Executing.front->ProcessNum << endl;
				}
				else
				{
					cout << "Now running:" << setw(4) << "CPU Idle\n";
					outputfile << "Now running:" << setw(4) << "CPU Idle\n";
				}
				cout << "......................................................\n";
				outputfile << "......................................................\n";

				//prints Ready
				if (Ready.front != 0)
				{
					cout << "/nReady Queue:" << setw(10) << "Process " << setw(8) << "Burst\n";
					outputfile << "/nReady Queue:" << setw(10) << "Process " << setw(8) << "Burst\n";

					PROCESS_NODE *p = Ready.front;

					while (p != 0)
					{
						cout << setw(15) << "P" << p->ProcessNum << setw(10) << p->CPU[0] << endl;
						outputfile << setw(15) << "P" << p->ProcessNum << setw(10) << p->CPU[0] << endl;
						p = p->next;
					}
				}
				else
				{
					cout << "\nReady Queue:" << setw(10) << "Process " << setw(8) << "Burst\n";
					cout << setw(22) << "[empty]\n";
					outputfile << "\nReady Queue:" << setw(10) << "Process " << setw(8) << "Burst\n";
					outputfile << setw(22) << "[empty]\n";
				}
				cout << "......................................................\n";
				outputfile << "......................................................\n";

				//prints IO
				if (IO.front != 0)
				{
					cout << "\nNow in I/O: " << setw(10) << "Process " << setw(8) << "Remaining I/O time\n";
					outputfile << "\nNow in I/O: " << setw(10) << "Process " << setw(8) << "Remaining I/O time\n";

					PROCESS_NODE *p = IO.front;

					while (p != 0)
					{
						cout << setw(15) << "P" << p->ProcessNum << setw(10) << " " << p->IO[0] << endl;
						outputfile << setw(15) << "P" << p->ProcessNum << setw(10) << " " << p->IO[0] << endl;
						p = p->next;
					}

				}
				else
				{
					cout << "\nNow in I/O: " << setw(10) << "Process " << setw(21) << "Remaining I/O time\n";
					cout << setw(22) << "[empty]\n";
					outputfile << "\nNow in I/O: " << setw(10) << "Process " << setw(21) << "Remaining I/O time\n";
					outputfile << setw(22) << "[empty]\n";

				}

				cout << "......................................................\n";
				outputfile << "......................................................\n";

				//prints completed processes
				if (COMPLETE.front != 0)
				{
					cout << "\nCompleted: " << setw(4);
					outputfile << "\nCompleted: " << setw(4);

					PROCESS_NODE *p = COMPLETE.front;

					while (p != 0)
					{
						cout << "P" << p->ProcessNum;
						outputfile << "P" << p->ProcessNum;

						if (p ->next != 0)
						{
							cout << ", ";
							outputfile << ", ";
						}

						p = p->next;
					}

					cout << endl;
					outputfile << endl;
				}


				cout << "......................................................\n";
				cout << "......................................................\n\n\n\n";
				outputfile << "......................................................\n";
				outputfile << "......................................................\n\n\n\n";

				ContextSwitch = 0;
				

			}

			//**************decrements IO in IO list and increases IOtime**********
			if (IO.front != 0)
			{
				PROCESS_NODE *p = IO.front;

				while (p != 0)
				{
					p->IO[0] = p->IO[0] - 1;
					p->IOtime = p->IOtime + 1;
					p = p->next;
				}
			}


			CurrentTime = CurrentTime + 1;
		}

		CurrentTime = CurrentTime - 1;


	//***********calculates CPU utilization*********************
		double TotalCPU = 0;

		PROCESS_NODE *c = COMPLETE.front;

		while (c != 0)
		{
			TotalCPU = TotalCPU + c->CPUtime;
			c = c->next;
		}

		double CPUutilization = (TotalCPU / CurrentTime) * 100;


		//************calculates average response, waiting an tunraround time
		double avgRT = 0;
		double avgWT = 0;
		double avgTT = 0;

		c = COMPLETE.front;

		while (c != 0)
		{
			avgRT = avgRT + c->ResponseTime;
			avgWT = avgWT + c->WaitTime;
			avgTT = avgTT + (c->WaitTime + c->IOtime + c->CPUtime);

			c = c->next;
		}

		avgRT = avgRT / 9;
		avgWT = avgWT / 9;
		avgTT = avgTT / 9;



	//***********prints total time, CPU utilization, response, wait and turnaround times**********

		cout << "Finished\n\n";
		outputfile << "Finished\n\n";

		cout << "Total Time:" << setw(11) << CurrentTime << endl;
		cout << "CPU Utilization:" << setw(10) << CPUutilization << "%\n\n";
		outputfile << "Total Time:" << setw(11) << CurrentTime << endl;
		outputfile << "CPU Utilization:" << setw(10) << CPUutilization << "%\n\n";

		//prints wait time
		cout << "Waiting Times" << setw(8) << "P1" << setw(5) << "P2" << setw(5) << "P3" << setw(5) << "P4" << setw(5) << "P5"
			<< setw(5) << "P6" << setw(5) << "P7" << setw(5) << "P8" << setw(6) << "P9\n";
		outputfile << "Waiting Times" << setw(8) << "P1" << setw(5) << "P2" << setw(5) << "P3" << setw(5) << "P4" << setw(5) << "P5"
			<< setw(5) << "P6" << setw(5) << "P7" << setw(5) << "P8" << setw(6) << "P9\n";
		
		cout << setw(22);
		outputfile << setw(22);

		c = COMPLETE.front;
		while (c != 0)
		{
			cout << c->WaitTime << setw(5);
			outputfile << c->WaitTime << setw(5);
			c = c->next;
		}

		cout << "\nAverage Wait:" << setw(13) << avgWT << endl << endl;
		outputfile << "\nAverage Wait:" << setw(13) << avgWT << endl << endl;

		//prints turnaround time
		cout << "Turnaround Times" << setw(5) << "P1" << setw(5) << "P2" << setw(5) << "P3" << setw(5) << "P4" << setw(5) << "P5"
			<< setw(5) << "P6" << setw(5) << "P7" << setw(5) << "P8" << setw(6) << "P9\n";
		outputfile << "Turnaround Times" << setw(5) << "P1" << setw(5) << "P2" << setw(5) << "P3" << setw(5) << "P4" << setw(5) << "P5"
			<< setw(5) << "P6" << setw(5) << "P7" << setw(5) << "P8" << setw(6) << "P9\n";
		
		cout << setw(22);
		outputfile << setw(22);
		
		c = COMPLETE.front;
		
		while (c != 0)
		{
			cout << (c->WaitTime + c->IOtime + c->CPUtime) << setw(5);
			outputfile << (c->WaitTime + c->IOtime + c->CPUtime) << setw(5);
			c = c->next;
		}

		cout << "\nAverage Turnaround:" << avgTT << endl << endl;
		outputfile << "\nAverage Turnaround:" << avgTT << endl << endl;
		

		//prints response time
		cout << "Response Times" << setw(7) << "P1" << setw(5) << "P2" << setw(5) << "P3" << setw(5) << "P4" << setw(5) << "P5"
			<< setw(5) << "P6" << setw(5) << "P7" << setw(5) << "P8" << setw(6) << "P9\n";
		outputfile << "Response Times" << setw(7) << "P1" << setw(5) << "P2" << setw(5) << "P3" << setw(5) << "P4" << setw(5) << "P5"
			<< setw(5) << "P6" << setw(5) << "P7" << setw(5) << "P8" << setw(6) << "P9\n";

		cout << setw(21);
		outputfile << setw(21);

		c = COMPLETE.front;

		while (c != 0)
		{
			cout << c->ResponseTime << setw(5);
			outputfile << c->ResponseTime << setw(5);
			c = c->next;
		}

		cout << "\nAverage Response:" << setprecision(5) << setw(8) << avgRT << endl << endl;
		outputfile << "\nAverage Response:" << setprecision(5) << setw(8) << avgRT << endl << endl;



	outputfile.close();

	return 0;

}




