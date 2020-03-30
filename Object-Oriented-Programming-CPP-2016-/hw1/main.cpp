//************************************************//
//            Burak AKTEN 141044045               // 
//                BIL 241 HW01                    //
//************************************************//
//Bu program dosyadan aşağıdaki talimatları       //
//okuyarak assembly kodunu verilen option ve dosya// 
//ismine göre calıştırır. Eğer dosyadaki talimat- //
//lar syntax ve register bakımından hatalı ise    //
// programı -1 return ederek sonlandırır.         //
//************************************************//
//                INSTRUCTIONS                    //
//************************************************//
//                MOV reg, reg                    //
//                MOV reg, constant               //
//                ADD reg, reg                    //
//                ADD reg, constant               //
//                SUB reg, reg                    //
//                SUB reg, constant               //
//                JMP reg, lineAdress             //
//                JMP lineAddress                 //
//                PRN reg                         // 
//                PRN constant                    //
//                HLT                             //
//************************************************//
#include <iostream>
#include <fstream>
#include <string>
#define SIZE 5

using namespace std;

void modifiedHlt(string& txt);
//Eger hlt komutu okundugunda "HLT;" seklinde ise bunu "HLT" yapar
bool controlTxt(string txt , string str[] , int size);
//bu fonksiyon verilen txt stringi verilen string array içinde ise true , 
//degilse false return eder.
bool isAllNumber(string txt);
// verilen stringin bütün indexlerinde rakam varsa true return eder.
void findSubStr( string& txt , string& txt2, string line );
// Bu fonksiyon gönderilen line stringini ',' ve ';' lere göre bölüp diğer
//    stringlere atar.
void makeUpper(string& txt);
// Bu fonksiyon alınan stringin bütün harflerini büyük harf yapar.
int convertStrToInt(string str);
// Bu fonksiyon verilen stringi integer' a cevirir.
int jump(string txt , int regArr[] , int size);
//Eğer txt stringi bi register'ı temsil ediyorsa ve registerın değeri sıfır ise
//  1(jump yapabilir) değerini return eder.
bool jump(ifstream& file, string txt ,string txt2 ,char* fName,int jumpVal 
		  ,int& currentLine);
// Eğer yukarıdaki ilk jump fonksiyonun return degeri 1(jumpVal) ise veya
//  diğer jump edeceği satır txt2 de verilmiş ise dosyada aç kapa işlemi ve 
//  satır okuma işlemi ile yeni satıra jump yapılır, currentLine update edilir.
// Eğer jump işlemini yapamassa false return eder.
bool move(string txt,string txt2,int regArr[] , int size);
// Bu fonksiyon txt ve txt2 stringlerini inceledikden sonra gerekli move
// işlemini yapar ve registerları(r1 ,r2 ,r3 ,r4 ,r5) günceller.
// Eğer taşıma işlemini yapamassa false return eder.
bool prnt(string txt , int regArr[] , int size);
// Bu fonksiyon verilen txt stringini inceler ve eğer registersa registerın
// degerini , eğer constant deger se dırek o degeri ekrana basar.
// Eğer print işlemini yapamassa false return eder.
bool subOrAdd
(string txt,string txt2,int regArr[] , int size,int value);
//Bu fonksiyon txt ve txt2 stringlerini inceledikden sonra gerekli toplama 
// veya çıkarma işlemini value (-1 or +1) değerine göre yapar.
// Value 1 ise toplama , -1 ise çıkarma işlemi yapar.
// Eğer gerekli işlemini yapamassa false return eder.

int main(int argc , char *argv[]){
     
    ifstream cpuFile; //Dosya üzerinden işlem yapmamız için gerekli olan object
    string mov="MOV",add = "ADD",jmp = "JMP",sub = "SUB",hlt ="HLT",prn = "PRN";
    //Dosyadaki talimatları anlamak için gerekli stringler.(karşılaştırma)
    string text , str ,text2;
    //dosyadan yapılan okumalarda alınan stringerin atanacağı strinler.
    int reg[SIZE] = {0,0,0,0,0};
    // Register ların ilk değerleri.
    bool control;
    // While dögüsünü kontrol etmek için gerekli.
         
    //Dosyadaki satır sayısını bulmak için yapılan işlem.
    cpuFile.open(argv[1]);    
  
    //dosyanın var olup olmadığına bakılıyor eğer yoksa error mesajı verilip 
    // program sona erdililiyor.
    if(cpuFile.fail()){
        
        cerr <<endl<< "That file could not found!!";
        return -1;
    }
    //Dosyadaki satır sayısını bulmak için yapılan işlem.
    // dosyanın sonuna kadar dosya satır satır okunuyor.
    int line = 0;
    while(getline(cpuFile , str)){
        line++;
    }
    cpuFile.close();
    
    //Talimatları gerçekleştirmek için dosya tekrar açılıyor.
    cpuFile.open(argv[1]); 
    switch(convertStrToInt(argv[argc - 1])){// option kontrolü.		
        case 0:
           //for döngüsü son satıra gelip gelmediğini kontrol ediyor. 
           for(int i = 1 ; i <= line  ; ++i){                
                cpuFile >> text ;
                // dosyadan okunan komutun her harfi büyük hale getiriliyor.
                makeUpper(text);
                modifiedHlt(text);
                if(text==mov || text==add || text==sub || text==hlt || text==prn
                        || text==jmp){
                    
                    control = true;
                    while(control){          
                        if(text == mov){                           
                            getline(cpuFile , str);
                            // bütün satır alınıp sub string hale getirilmek 
                            // için findSubStr fonksiyonuna gonderiliyor.
                            findSubStr(text , text2, str);
                            //eğer text2 boş ise komutda hata vardır.
                            if (text2 == ""){
                            	cerr << "SYNTAX ERROR!!"<<endl;
                            	return -1 ;
                            }             
                            if(!move(text,text2,reg , SIZE)){
                                // move fonksiyonu gerçekleşmiyorsa program 
                                // bitiriliyor.
                                cerr<< "REGISTER/NUMBER ERROR!!!"<<endl;
                                return -1;
                            }
                            control = false ;
                        }
                        else if(text == prn){                            
                            getline(cpuFile , str);
                            findSubStr(text , text2, str);
                            
                            if(text2 == ""){
                                if(!prnt(text,reg , SIZE)){
                                    // prnt fonksiyonu gerçekleşmiyorsa program 
                                    // bitiriliyor.
                                    cerr<< "REGISTER ERROR!!!"<<endl;
                                    return -1;
                                }
                                cout << endl;
                            }
                            else{
                            	 cerr<< "SYNTAX ERROR!!!"<<endl;
                                 return -1;
                            }
                            control = false;
                        }
                        else if(text == hlt){
                            //program bitirilir.
                            //ama ilk önce hlt ın bulunguğu satırı kontrol eder.
                            // halt komutundan sonra birşey yazılmış mı diye 
                            // eger komut yanlız degilse -1 return edilir
                            getline(cpuFile , str);
                            findSubStr(text , text2 , str);
                            if(text != "" || text2 != ""){
                                cerr<<"SYNTAX ERROR IN LAST LINE!!"<<endl;
                                return -1;
                            }
                            return 0;            
                        }
                        else if(text == add || text == sub){        
                            
                            int minusOrPlus = (text == add ? 1 : -1);
                            // minusOrPlus'a text add 'e eşitse +1 , değilse -1
                            // atanıyor.
                            getline(cpuFile , str);
                            findSubStr(text , text2, str);
                            if (text2 == ""){
                            	cerr << "SYNTAX ERROR!!"<<endl;
                            	return -1 ;
                            }   
                            if(!subOrAdd
                                 (text ,text2 ,reg,SIZE,minusOrPlus))
                            {
                                // subOrAdd fonksiyonu gerçekleşmiyorsa program 
                                // bitiriliyor.
                                cerr << "REGISTER/NUMBER ERROR!!!"<<endl; 
                                return -1;
                            }
                            control = false ;
                        }
                        else if(text == jmp){
                            
                            getline(cpuFile , str);
                            findSubStr(text , text2, str);
                            
                            int jmpVal = jump(text,reg , SIZE);
                            // text de register varsa ve sıfırsa jmpVal'a 1 
                            // atanır.
                            if(!jump(cpuFile, text ,text2 ,argv[1],jmpVal,i) ||
                                    i > line){
                               // jump fonksiyonu gerçekleşmiyorsa program 
                               // bitiriliyor.
                               cerr << "REGISTER/LINE ERROR!!!"<<endl; 
                               return -1;
                            }
                            control = false;
                        }                            
                    }
                }
                else{ // ilk okunan değer add,sub,jmp,hlt... ile eşleşmiyorsa
                      // error mesajı verilip program biter.
                    cerr <<endl<< "Syntax Error In Instructions!" <<endl;
                    return -1;
                }
            }break;	      
        case 1:
             // bu case için ilk casedeki işlemler yapılır artı olarak her 
            //  talimat ve register degeri yazılır ekrana.
            cpuFile >> text ;
            for(int i = 1 ; i <= line ; ++i){                
                makeUpper(text);
                modifiedHlt(text);
                if(text==mov || text==add ||text==sub || text==prn | text==jmp
                        || text == hlt){
                    control = true;
                    cout << text;
                    while(control){                    
                        if(text == mov){                                                    
                            getline(cpuFile , str);
                            findSubStr(text , text2, str);
                            if (text2 == ""){
                            	cout << " "<< text << endl;
                            	cerr << "SYNTAX ERROR!!"<<endl;
                            	return -1 ;
                            }                                   
                            if(!move(text,text2,reg ,SIZE)){
                                cout << " "<< text << "," <<text2;
                                cerr <<endl<< "REGISTER/NUMBER ERROR!!!"<<endl;
                                return -1;
                            }
                            cout<< " "<< text<<","<< text2;
                            control =  false ;
                        }
                        else if(text == prn){                         
                            getline(cpuFile , str);
                            findSubStr(text , text2, str);
                            
                            cout <<" "<<text;
                            
                            if(text2 == ""){
                                if(!prnt(text, reg , SIZE)){
                                    cerr<<endl<< "REGISTER ERROR!!!"<<endl;
                                    return -1;
                                }
                            }
                            else{
                            	 cerr << ","<<text2<<endl;
                            	 cerr<< "SYNTAX ERROR!!!"<<endl;
                                 return -1;
                            }                                                                                          
                            control = false;
                        }
                        else if(text == hlt){
                            getline(cpuFile , str);
                            findSubStr(text , text2 , str);
                            if(text != "" || text2 != ""){
                            	cout << " "<<text << text2;;
                                cerr<<endl<<"SYNTAX ERROR IN LAST LINE!!"<<endl;
                                return -1;
                            }
                            cout<<"-R1="<<reg[0]<<","<<"R2="<<reg[1]<<",";
                            cout<<"R3="<<reg[2];
                            cout<<","<<"R4="<< reg[3]<<","<<"R5="<<reg[4]<<endl; 
                            return 0;            
                        }
                        else if(text == add || text == sub){                            
                            int minusOrPlus = (text == add ? 1 : -1);
                            
                            getline(cpuFile , str);
                            findSubStr(text , text2, str);
                            if (text2 == ""){
                            	cout << " "<< text << endl;
                            	cerr << "SYNTAX ERROR!!"<<endl;
                            	return -1 ;
                            } 
                            if(!subOrAdd(text ,text2 , reg ,SIZE ,minusOrPlus)){
                                cout << " " << text << "," << text2<<endl;
                                cerr << "REGISTER/NUMBER ERROR!!!"<<endl;                        
                                return -1;
                            }
                            cout<< " "<<text<<","<< text2 ;
                            control = false ;
                        }
                        else if(text == jmp){                          
                            getline(cpuFile , str);
                            findSubStr(text , text2, str);
                            
                            cout << " " <<text;
                                                        
                            int jmpVal = jump(text,reg , SIZE);
                            
                            if(!jump(cpuFile, text ,text2 ,argv[1],jmpVal,i) ||
                                    i > line){
                               // jump fonksiyonu gerçekleşmiyorsa program 
                               // bitiriliyor.  
                               if(text2 != "")
                               cout << "," << text2 ;
                               cerr <<endl <<"REGISTER/LINE ERROR!!!"<<endl; 
                               return -1;
                            }
                            if(text2 != "")
                            	cout << "," << text2 ;
                            control = false;
                        }
                    }
                }
                else{ 
                    cerr <<endl<< "Syntax Error In Instructions!"<<endl;
                    return -1;
                }                
                cout<<"-R1="<<reg[0]<<","<<"R2="<<reg[1]<<","<<"R3="<<reg[2];
                cout<<","<<"R4="<< reg[3]<<","<<"R5="<<reg[4]<<endl;
                
                cpuFile >> text ;      
            }break;		        
        default :
            // error mesajı verilir ve program bitirilir.
            cerr <<endl<< "Command Error!!"<<endl;
            return -1;
            break;
    }	
    return 0;
}
bool move(string txt,string txt2,int regArr[] , int size){   

    string strReg[SIZE] = {"R1","R2","R3","R4","R5"};
    
    if(isAllNumber(txt2)){
    	//bu koşula ikinci string tamammen rakamdan oluşuyorsa  
        //giriliyor ve registerlar update ediliyor txt2 integer a çevrilerek.
        
        //eğer txt belirtilmeyen register ise fonksiyon false return eder.
        if(!controlTxt(txt , strReg , SIZE))
            return false;
        
        for(int i = 0 ; i < size ; ++i)
            if(txt == strReg[i])
        	regArr[i] = convertStrToInt(txt2);
    }
    else if(!isAllNumber(txt2) && !isAllNumber(&txt2[1]))
        return false;
    else{//Bu koşula ise her ikiside register ise girer ve move işlemi yapar.
        
        if(!controlTxt(txt , strReg , SIZE) && !controlTxt(txt2, strReg , SIZE))
            return false;
        
    	for(int i = 0 ; i < size ; ++i)
            for(int j = 0 ; j < size ; ++j)
    		if(txt == strReg[i] && txt2 == strReg[j])
                    regArr[j] = regArr[i];
    }
    return true;
}
bool prnt(string txt , int regArr[] , int size){

    string strReg[SIZE] = {"R1","R2","R3","R4","R5"};

    //verilen txtnin indexleri tamamen rakam içeriyorsa direk orakam ekrana
    // yazılır aksi taktirde txt nin temsil etdiği regsterın değeri yazılır.
    if(isAllNumber(txt))
        cout << " <" <<convertStrToInt(txt)<< "> " ;
    else{       
        if(!controlTxt(txt , strReg , SIZE))
            return false; 
        
    	for(int i = 0; i < size ; ++i)
            if(txt == strReg[i])
                cout << " <"<<regArr[i] << "> ";
    }
    return true;
}
bool subOrAdd(string txt,string txt2,int regArr[], int size ,int value){
    //bu fonksiyoda da txt ve txt2 stringlerini velirlemek için move 
    //fonksiyonunda yapılan işlemler yapılıyor farklı olarak burada 
    // value değerine göre çıkarma yada toplama işlemi yapılıyor.
    string strReg[SIZE] = {"R1","R2","R3","R4","R5"};	
	
    if(isAllNumber(txt2)){  	
        if(!controlTxt(txt , strReg , SIZE))
            return false;  
    	for(int i = 0 ; i < size ; ++i)
            if(txt == strReg[i])
       		regArr[i] = regArr[i] + (value) * convertStrToInt(txt2);
    }
    else if(!isAllNumber(txt2) && !isAllNumber(&txt2[1]))
        return false;
    else{
        if(!controlTxt(txt , strReg , SIZE) && !controlTxt(txt2, strReg , SIZE))
            return false;
        
    	for(int i = 0 ; i < size ; ++i)
            for(int j = 0 ; j < size ; ++j)
    		if(txt == strReg[i] && txt2 == strReg[j])
                    regArr[i] = regArr[i] + (value) * regArr[j];
    }
    return true;
}
int convertStrToInt(string str){

    // len verilen stringin uzunluğunu , sum ise çevrilecek sayıyı temsil eder.
    int len = str.length() , sum = 0;
    int temp = len;

    //ilk for dönüsünde stringin sonuna kadar gider her indexdeki rakamı
    //  integera cevirip sum a eklenir.
    // ikinci for döngüsünde ise pow işlemi yapılır.
    for(int i = 0 ; i < len; ++i ,--temp){
        int pow = 1 ;
        for(int j = 1 ; j <= temp - 1 ; j++ )
            pow *= 10;       
        sum += (str[i] - 48) * pow;
    }	
    return sum;
}
bool controlTxt(string txt , string str[] , int size){
    for(int i = 0; i < size ; ++i)
        if(txt == str[i])
            return true;
    return false;
}
void findSubStr( string& txt , string& txt2, string line ){

    // ilk önce verilen strigler boşaltılır.
    txt = "";
    txt2 = "";   
    //daha sonra virgül ve noktalı virgül olma durumlarına göre verilen string
    // sub stringlere bölünür ve bunlar txt ve txt2 stringlerine atanır.
    // eğer virgül yoksa txt2 boş kalır. Varsa noktalı virgül var olm durumuna
    // göre txt2 ye bir substring atanır.
    
    int index = line.find_first_of(',');
    if(index >= 0){//virgül kontrolü
        txt = line.substr(0 , index);
        
        int index2 = line.find_first_of(';');

        if(index2 >= 0)//noktalı virgül kontrolü
            txt2 = line.substr(index + 1 , index2 - (index + 1));
        else
            txt2 = line.substr(index + 1 , line.size() - (index + 1));
        
        index = txt2.find_first_of(' ');
        while(index >= 0){
            txt2.erase(index , 1);
            index = txt2.find_first_of(' ');
        }
    }
    else{//noktalı virgül kontrolü
        index = line.find_first_of(';');        
        if(index >= 0)
            txt = line.substr(0 , index);
        else
            txt = line.substr(0 , line.size()); 
    }
   
    index = txt.find_first_of(' ');
    while(index >= 0){    
        txt.erase(index , 1);
        index = txt.find_first_of(' ');
    }
    //en son bulunan substringler eğer küçük harf içeriyorsa büyültülürler.
    makeUpper(txt);
    makeUpper(txt2);  
}
void makeUpper(string& txt){
    // Bu fonksiyon alınan stringin bütün harflerini büyük harf yapar.
    for(int i = 0 ; i < txt.size() ; ++i)        
        if(txt[i] >= 'a' && txt[i] <= 'z')
            txt[i] -= 'a' - 'A';
}
bool jump(ifstream& file, string txt ,string txt2 , char* fName,
		  int jumpVal , int& currentLine){
    string strReg[SIZE] = {"R1","R2","R3","R4","R5"};
    string buffer;//jump yaparken üstünden geçilen satırlar buffera atılır.
    int line; 
    bool ctrl = true;
    
    if(txt2 != "" && isAllNumber(txt2)){//iki farklı jump komutu oldugundan 
                   //dolayı eger ikinci string boş ise bu koşul yapılır
        
        if(!controlTxt(txt , strReg , SIZE))
            ctrl = false;
        
        line = convertStrToInt(txt2); //line değeri atanıyor.
        //currentline  ve line arasında ki ilişkiye göre işlemler yapılır
        //eger jumpVal koşulu sağlanırsa.
        if(jumpVal && line > currentLine){                      
	   for(int count=currentLine + 1;count < line ; ++count)
	       	getline(file , buffer);//satırlar atlanır
            currentLine = line - 1;//currentLine update ediliyor.
	}
        else if(jumpVal && line<currentLine){                                    
            file.close();
            file.open(fName);
            for(int count=1;count<line; ++count)
                getline(file , buffer);
            currentLine = line - 1;
        }                               
    }
    else if(txt2 == "" && isAllNumber(txt)){
        //eğer direk line numarası verilmişse bu koşul gerçeklesir
        line = convertStrToInt(txt);                                                            
        if(line > currentLine){
           for(int count=currentLine + 1;count < line; ++count)
               getline(file , buffer);
            currentLine = line - 1;
        }
        else if(line<currentLine){
	    file.close();
            file.open(fName);
            for(int count=1 ; count < line; ++count)
                getline(file , buffer);
            }
            currentLine = line - 1;
    }
    else
        ctrl = false;
    return ctrl;
}
int jump(string txt , int regArr[] , int size){
    //Eğer txt stringi bi register'ı temsil ediyorsa ve registerın değeri sıfır 
    // ise 1(jump yapabilir) değerini return eder.
    string strReg[SIZE] = {"R1","R2","R3","R4","R5"};
    bool ctrl = false;
    
    for(int i = 0 ; i < size ; ++i){
    	if(txt == strReg[i] && regArr[i] == 0)
    		ctrl = true;
    }
    if(ctrl)
    	return 1;   
    return 0;
}
bool isAllNumber(string txt){
    // verilen stringin bütün indexlerinde rakam varsa true return eder.
    bool ctrl = true;
    for(int i = 0 ; i < txt.size(); ++i)
        if(!(txt[i] >= '0' && txt[i] <= '9'))
            ctrl = false;
    return ctrl;
}
void modifiedHlt(string& txt){
	if(txt[0] == 'H' && txt[1] == 'L' && txt[2] == 'T' &&txt[3] == ';' )
		txt = "HLT";
}
