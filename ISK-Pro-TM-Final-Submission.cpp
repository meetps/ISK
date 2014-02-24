//Industrial Stock Keeper Pro TM
//CS101-Project by-Meet P Shah(13D070003 & Akshay Deodhar(13D100002)
//Header Files
#include<fstream>
#include<string>
#include<sstream>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cstdlib>
#include <ctime>
#include<math.h>
using namespace std;

int stoi(string s) {															//convert string to integer
	int l , x , n = 0 , p;
	char c;
	l = s.length();
	for(x = l-1 ; x >=0 ; x--) {
		c = s[x];
		p = c;
		p = p - 48;
		n = n + p*pow(10.0,l-1-x);
	}
	return n;
}

float stof(string s) {															//convert string to float
	int x ;
	x = s.find('.');
	string left , right;
	left = s.substr(0 ,x);
	right = s.substr(x+1);
	int a , b;
	a = stoi(left);
	b = stoi(right);
	float p = pow(10.0 , x + 1.0 - s.length());
	float num = a + b*p;
	return num;
}

string Convert (float number){                                                  //Float to String Converter
      std::ostringstream buff;
      buff<<number;
      return buff.str();
	}

 string gettime()                                                               // To Access the system Time
{
       time_t now = time(0);
       string dt = string(ctime(&now));
       tm *gmtm = gmtime(&now);
       dt = asctime(gmtm);
       return dt;
}


class order                                                                             //class of company/firm
{
       public :
       int matcount,procount,ordercount,srnoo[1000];
       string date[1000],month[1000],day[1000],timex[1000],proname[1000],quant[1000];  //atributes of the order
       order()
           {
            matcount=0;
            procount=0;
            ordercount=0;
           }
       string srnom[100],mname[100],unit[100],prod[100],quantity[100],threshold[100];  //atributes of materials

      string  srnop[100],pname[100],mat[100],matcnt[100],waste[100],use[100];          //atributes of materials
//Member Functions

void initialize();                                                              //To initialize variables from files
void process();                                                                 //To manufacture listed products 
void addmat();                                                                  //To add materials
void addpro();                                                                  //To add Products
void displaypro();                                                              //To display listed products
void displaystock();                                                            //To display listed materials
void renewstock();                                                              //To renew the materials
void disprev();                                                                 //To display previous orders
void reminder();                                                                //To display the reminder for renewing materials
void print()
  { ofstream mate;
    mate.open("materials.txt",ios::out);
    ofstream prod;
    prod.open("products.txt",ios::out);
   for(int i=1;i<=matcount;i++)
	{
	  mate<<srnom[i]<<" "<<mname[i]<<" "<<unit[i]<<" "<<quantity[i]<<" "<<threshold[i]<<endl;
	}

  for(int i=1;i<=procount;i++)
	{
	  prod<<srnop[i]<<" "<<pname[i]<<" "<<matcnt[i]<<" "<<mat[i]<<" "<<waste[i]<<" "<<use[i]<<endl;
	}


  }
};

   void  order::initialize()
  {  ifstream mate;
     mate.open("materials.txt",ios::in);
     ifstream prod;
     prod.open("products.txt",ios::in);
     ifstream o;
     o.open("order.txt",ios::in);



     string tempro;
     while(getline(prod,tempro,'\n'))
            {
                    procount ++;
                    int space[5],k=0;
			for(int i=0;i<tempro.length();i++)
                   { if(tempro[i]==' ')
                         {
								space[k++]=i;
                         }
                   }

           srnop[procount]=tempro.substr(0,space[0]);
           pname[procount]=tempro.substr(space[0]+1,space[1]-space[0]-1);
           matcnt[procount]=tempro.substr(space[1]+1,space[2]-space[1]-1);
           mat[procount]=tempro.substr(space[2]+1,space[3]-space[2]-1);
           waste[procount]=tempro.substr(space[3]+1,space[4]-space[3]-1);
           use[procount]=tempro.substr(space[4]+1,tempro.length()-space[4]-1);

            }


             string tempmat;
             while(getline(mate,tempmat,'\n'))
            {       matcount++;
                    int space[4],k=0;
			for(int i=0;i<(tempmat.length());i++)
                   { if(tempmat[i]==' ')
                         space[k++]=i;
                   }

           srnom[matcount]=tempmat.substr(0,space[0]);
           mname[matcount]=tempmat.substr(space[0]+1,space[1]-space[0]-1);
           unit[matcount]=tempmat.substr(space[1]+1,space[2]-space[1]-1);
           quantity[matcount]=tempmat.substr(space[2]+1,space[3]-space[2]-1);
           threshold[matcount]=tempmat.substr(space[3]+1,tempmat.length()-space[3]-1);
            }

	  string tempo;
	  while(getline(o,tempo,'\n'))
           {
		   ordercount++;
                int space[5],k=0;
			for(int i=0;i<(tempo.length());i++)
                   { if(tempo[i]==' ')
                         space[k++]=i;
                   }
           srnoo[ordercount]=ordercount;
           date[ordercount]=tempo.substr(space[0]+1,space[1]-space[0]-1);
           month[ordercount]=tempo.substr(space[1]+1,space[2]-space[1]-1);
           day[ordercount]=tempo.substr(space[2]+1,space[3]-space[2]-1);
           timex[ordercount]=tempo.substr(space[3]+1,space[4]-space[3]-1);
           proname[ordercount]=tempo.substr(space[4]+1,space[5]-space[4]-1);
           quant[ordercount]=tempo.substr(space[5]+1,tempo.length()-space[5]-1);
           }

  }

   void order ::disprev()
  {     int prev=0;
		cout<<"Enter the number of previous orders to be displayed :"<<endl;
		cin>>prev;
		for(int i=ordercount;i>ordercount-prev;i--)
                   {
						  cout<<srnoo[i]<<" "<<date[i]<<" "<<month[i]<<" "<<day[i]<<" "<<timex[i]<<" "<<proname[i]<<"    "<<quant[i]<<endl;
                   }
  }


   void order ::displaystock()
  {
          for(int i=1;i<=matcount;i++)
	{
	         cout<<srnom[i]<<" "<<mname[i]<<" "<<unit[i]<<" "<<quantity[i]<<" "<<threshold[i]<<endl;
	}

 	//Displays current stock;analog of ls in shell

  }



   void order ::renewstock()
  {    string renew;
       float renewamt=0,original=0;
       displaystock();//see wheter order.display has to be put
       cout<<endl<<endl<<"Enter the Serial No of the Material "<<endl;
       cin>>renew;
       cout<<endl<<endl<<"Enter Renewal Amount (Specified Units) of the Material :"<<endl;
       cin>>renewamt;


       for(int i=1;i<=matcount;i++)
          {
             if(srnom[i]==renew)
               { istringstream(quantity[i])>>original;
                 original+=renewamt;
	         quantity[i]=Convert(original);                //float to string
				 cout<<endl<<"Stock renewed Sucessfully : Changed Stock :"<<"  "<<original <<" "<<unit[i]<<endl;
				 break;
			   }
          }
  }



   void order ::addmat()
  {
        cout << "Enter the Name of the Material" <<endl;
        cout<< " Note-Keep underslashes between words in case name consists of multiple words "<<endl;
        cin >> mname[matcount+1];
        cout << "Enter the Unit of the Material-(eg-nos,metres)" <<endl;
        cin >> unit[matcount+1];
        cout << "Enter the present Quantity of the Material in specified Units :" <<endl;
        cin >> quantity[matcount+1];
        cout << "Enter the Threshold Quantity of the Material in specified Units :" <<endl;
        cin >> threshold[matcount+1];
        srnom[matcount+1]=Convert(matcount+1);
        matcount++;
        cout<<"  Material Added Succesfully :"<<endl;
  }

   void order ::addpro()
  {
        cout << "Enter the Name of the Product" <<endl;
        cout<< " Note-Keep underslashes between words in case name consists of multiple words "<<endl;
        cin >> pname[procount+1];
        cout <<endl<<endl<< "Enter the No of Materials to be used" <<endl;
        cin >> matcnt[procount+1];
        cout <<endl<< "Enter the Materials (Press Enter b/w two inputs) :" <<endl;

		int mtcnt;
        std::istringstream ss(matcnt[procount+1]);
        ss >> mtcnt;

              string cmat[mtcnt];
              for(int i=0;i<mtcnt;i++)
                 {
                    cin>>cmat[i];
                    mat[procount+1]+=cmat[i]+"*";
                 }
        string sam=mat[procount+1].substr(0, mat[procount+1].length()-1);
        mat[procount+1]=sam;




        string cmatuse[mtcnt];
        cout <<endl<< "Enter the Usage of Materials as Directed in specified Units :" <<endl;
              for(int i=0;i<mtcnt;i++)
                 {
                    cout<<cmat[i]<<"  : ";
                    cin>>cmatuse[i];
                    use[procount+1]+=cmatuse[i]+"*";
                 }
        string samu=use[procount+1].substr(0, use[procount+1].length()-1);
        use[procount+1]=samu;




        string cmatwaste[mtcnt];
        cout <<endl<< "Enter the Wastage of Materials as Directed in Percentage :" <<endl;
              for(int i=0;i<mtcnt;i++)
                 {
                    cout<<cmat[i]<<"  : ";
                    cin>>cmatwaste[i];
                    waste[procount+1]+=cmatwaste[i]+"*";
                 }
         string samw=waste[procount+1].substr(0, waste[procount+1].length()-1);
        waste[procount+1]=samw;



        srnop[procount+1]=Convert(procount+1);
        
        procount++;
        cout<<"  Product Added Succesfully :"<<endl;
       
  }

   void order ::displaypro()
  {

       for(int i=1;i<=procount;i++)
          {
				int mcount;
              std::istringstream ss(matcnt[i]);
              ss >> mcount;

              cout<<endl<<srnop[i]<<" "<<pname[i]<<"  "<<" No of Materials used :"<<matcnt[i]<<endl;//<<matcnt[i]<<use[i]<<waste[i]<<endl;
              int ast[mcount-1],k=0;
               string tmat=mat[i]+"*";
	      for(int j=0;j<(tmat.length());j++)
                   { if(tmat[j]=='*')
                         ast[k++]=j;
                   }

              int astu[mcount-1];
              k=0;
              string tmatu=use[i]+"*";
	      for(int j=0;j<(tmatu.length());j++)
                   { if(tmatu[j]=='*')
                         astu[k++]=j;
                   }
              int astw[mcount-1];
              k=0;
               string tmatw=waste[i]+"*";
	      for(int j=0;j<(tmatw.length());j++)
                   { if(tmatw[j]=='*')
                         astw[k++]=j;
                   }

                for(int k=0;k<mcount;k++)
                   { if(k==0)
                        {
                         cout <<"       "<<tmat.substr(k,ast[k])<<" "<<tmatu.substr(k,astu[k])<<" "<<tmatw.substr(k,astw[k])<<endl;
                        }
                      else
                        {
                          cout <<"       "<<tmat.substr(ast[k-1]+1,ast[k]-ast[k-1]-1)<<" "<<tmatu.substr(astu[k-1]+1,astu[k]-astu  [k-1]-1)<<" "<<tmatw.substr(astw[k-1]+1,astw[k]-astw[k-1]-1)<<endl;
                        }
                    }

            }
  }



void order::reminder()
{   int flag=0;
	for(int l=1;l<=matcount;l++)
			{
								if(stof(quantity[l])<=stof(threshold[l]))
						{
							flag++;
							cout<<"Material "<<mname[l]<<" "<<"quantity is critical :  "<<quantity[l]<<" "<<unit[l]<<" Renew it ASAP :"<<endl;
						}


			}

			if (flag==0)
                 {
						 cout<<"No Other Reminders to Display :"<<endl<<"All other Materials above Threshold :"<<endl;
                 }
}

void order::process()
{   string orderind;
	int ord,mcount;
	float quan;
	int pfound;
   //Printing Products To enable the user to choose from them
	for(int i=1;i<=procount;i++)
	{
		cout<<srnop[i]<<" "<<pname[i]<<endl;
  	}

  //taking product index to be processed
  	cout<<"Enter the Product No. to be processed : "<<endl;
	cin>>orderind;
	string tmat,tmatu,tmatw;
	for (int i=1;i<=procount;i++)
	{
		if (orderind==srnop[i])
		{   pfound=1;
			ord=i;
	    }
	    	else
 		{
			 pfound=0;
			}

    }
    

			cout<<"Enter the quantity in specified units : "<<endl;
			cin>>quan;
            mcount=stoi(matcnt[ord]);
              int ast[mcount-1],k=0;
               tmat=mat[ord]+"*";
	      for(int j=0;j<(tmat.length());j++)
                   { if(tmat[j]=='*')
                         ast[k++]=j;
                   }

              int astu[mcount-1];
              k=0;
               tmatu=use[ord]+"*";
	      for(int j=0;j<(tmatu.length());j++)
                   { if(tmatu[j]=='*')
                         astu[k++]=j;
                   }
              int astw[mcount-1];
              k=0;
               tmatw=waste[ord]+"*";
	      for(int j=0;j<(tmatw.length());j++)
                   { if(tmatw[j]=='*')
                         astw[k++]=j;

                   }






             //now iterating as many timesas no of maaterials
               for(int a=0;a<mcount;a++)
                     { //for each mateial
                      float q;
                     if(a==0)
                          { float w,u;
                         string tempname=tmat.substr(0,ast[0]);
                         //matching material name
                         for(int l=1;l<=matcount;l++)
                          {
                          	if(tempname==mname[l])
                          	{
                          		 q=stof(quantity[l]);
                                 w=stof(tmatw.substr(0,astw[0]));
                                 u=stof(tmatu.substr(0,astu[0]));
                                 q=q-(quan*(u+u*(.01*w)));
                                		if(q>0)
                          								{
                         								 quantity[l]=Convert(q);
						  								}
						  					else
                                      					{
															cout <<" Transaction not possible : Materials getting overused "<<endl;
                                      					}

                          	}
                          	else
							   {
                          	   }

                          }


                          }

                         else
                           {
								float qnext,w,u;
                           string tempname= (tmat.substr(ast[a-1]+1,ast[a]-ast[a-1]-1));

                                  for(int l=1;l<=matcount;l++)
                          {
                          	if(tempname==mname[l])
                          	{
                          		qnext=stof(quantity[l]);
                                w=stof(tmatw.substr(astw[a-1]+1,astw[a]-astw[a-1]-1));
                             u=stof(tmatu.substr(astu[a-1]+1,astu[a]-astu[a-1]-1));
                            qnext=qnext-(quan*(u+u*(.01*w)));
                              if(qnext>0)
                          								{
                         								 quantity[l]=Convert(qnext);
						  								}
						  					else
                                      					{
															cout <<" Transaction not possible : Materials getting overused "<<endl;
                                      					}
                          	}


                            }

		                    }

         }

	ordercount++;
    quant[ordercount]=Convert(quan);
    string time =gettime();
	day[ordercount]=time.substr(0,3);
	month[ordercount]=time.substr(4,3);
	date[ordercount]=time.substr(8,2);
	timex[ordercount]=time.substr(11,8);
	proname[ordercount]=pname[ord];
	srnoo[ordercount]=ordercount;
	print();
	 ofstream o;
    o.open("order.txt",ios::app);
    	o<<srnoo[ordercount]<<" "<<date[ordercount]<<" "<<month[ordercount]<<" "<<day[ordercount]<<" "<<timex[ordercount]<<" "<<proname[ordercount]<<" "<<quant[ordercount]<<endl;

}



int main()
{     order namaskar;
      int f=0,ch=0;
      namaskar.initialize();
     
      while(f==0)
           {
  	     cout << "Welcome to Industrial Stock Keeper Pro TM"<<endl<<endl;
  	     cout << "0. View Reminders :"<<endl;
         cout << "1. Process Order :"<<endl;
  	     cout << "2. View Stock : " <<endl;
 	     cout << "3. View Products : "<<endl;
  	     cout << "4. Add New Material : "<<endl;
 	     cout << "5. Add New Product : " << endl;
  	     cout << "6. Renew Stock : " << endl;
  	     cout << "7. View Previous Orders : " << endl;
  	     cout << "8. Save Changes : " << endl;
         cout << "9. Close : " << endl<<endl;
  	     cin >> ch;
		switch(ch)
                 {
		case 0 : namaskar.reminder();f=0;break;
		case 1 : namaskar.process();f=0;break;
  		case 2 : namaskar.displaystock();f=0;break;
  		case 3 : namaskar.displaypro();f=0;break;
  		case 4 : namaskar.addmat();namaskar.print();f=0;break;
  		case 5 : namaskar.addpro();namaskar.print();f=0;break;
  		case 6 : namaskar.renewstock();namaskar.print();f=0;break;
 		case 7 : namaskar.disprev();f=0;break;
 		case 8 : namaskar.print();f=0;break;
		case 9 : f=1;break;
  		default : cout << " Invalid Choice !"<<endl;f=0;
                }
	   if(f==0)
				{ for (int i=0;i<5;i++)cout<< " "<<endl;
				}

    }
}

//end of code

