//************************************************//
//            Burak AKTEN 141044045               //
//                BIL 241 HW02                    //
//************************************************//
//Bu program dosyadan aşağıdaki talimatları       //
//okuyarak assembly kodunu verilen option ve dosya//
//ismine göre calıştırır. Eğer dosyadaki talimat- //
//lar syntax ve register bakımından hatalı ise    //
// programı -1 return ederek sonlandırır.         //
// elimizde 5 tane register ve max 50 lik bir     //
// memory bulunmaktadır ve kod bunlara göre       //
// çalısmaktadır.                                 //
//************************************************//
//                INSTRUCTIONS                    //
//************************************************//
//                MOV reg, reg                    //
//                MOV reg, constant               //
//                MOV reg , address               //
//                MOV address , reg               //
//                MOV address ,constant           //
//                ADD reg, constant               //
//                ADD reg, reg                    //
//                ADD reg, address                //
//                SUB reg, reg                    //
//                SUB reg, constant               //
//                SUB reg, address                //
//                JMP reg, lineAdress             //
//                JPN reg, lineAdress             //
//                JMP lineAddress                 //
//                PRN reg                         //
//                PRN constant                    //
//                PRN address                     //
//                HLT                             //
//************************************************//
#include <iostream>
#include <fstream>
#include <string>
#define SIZE 5

using namespace std;

int option0(ifstream& file , int line , int memArr[] , int memSize,int regArr[]
            ,int regSize , char* fName);
// bu fonksiyon 0 komutu girildiğinde çalışır.
int option12(ifstream& file , int line , int memArr[] ,int memSize ,int regArr[]
             ,int regSize , char* fName , int option);
// bu fonksiyon ise 1 veya 2 komutu girildiginde çalışır.
int calculateNumOfline(ifstream& file , char* fName );
//bu fonksiyon dosyadaki line sayısını hesaplar ve return eder. Eger dosya yoksa
//-1 return eder.
void prntRegAndValuesInMemory
(int regArr[] , int size , int memArr[],int size2 , int command = 0);
//bu fonksiyon geçerli register degerlerini ve belirlenen memorideki değerleri
//ekrana yazar.
void modifiedHlt(string& txt);
//Eger hlt komutu okundugunda "HLT;" seklinde ise bunu "HLT" yapar
bool controlTxt(string txt , string str[] , int size);
//bu fonksiyon verilen txt stringi verilen string array içinde ise true ,
//degilse false return eder.
bool isAllNumber(string txt);
// verilen stringin bütün indexlerinde rakam varsa true return eder.
void findSubStr( string& txt , string& txt2,string line);
// Bu fonksiyon gönderilen line stringini ',' ve ';' lere göre bölüp diğer
//    stringlere(txt ve txt2) atar.
void makeUpper(string& txt);
// Bu fonksiyon alınan stringin bütün harflerini büyük harf yapar.
int convertStrToInt(string str);
// Bu fonksiyon verilen stringi integer' a cevirir.
int jump(string txt , int regArr[] , int size);
//Eğer txt stringi bi register'ı temsil ediyorsa ve registerın değeri sıfır ise
//  1(jump yapabilir) değerini return eder.
int jpnn(string txt , int regArr[] , int size);
//bu fonksiyonun jump adındaki aynı parapmetreleri alan fonksiyondan tek farkı
// temsil edilen register sıfırdan küçük oldugu zamanda da fonksiyon 1 döner.
bool jump(ifstream& file, string txt ,string txt2 ,char* fName,int jumpVal
		  ,int& currentLine);
// Eğer yukarıdaki ilk jump fonksiyonun return degeri 1(jumpVal) ise veya
//  diğer jump edeceği satır txt2 de verilmiş ise dosyada aç kapa işlemi ve
//  satır okuma işlemi ile yeni satıra jump yapılır, currentLine update edilir.
// Eğer jump işlemini yapamassa false return eder.
bool
move(string txt,string txt2,int regArr[] , int size , int memArr[] , int size2);
// Bu fonksiyon txt ve txt2 stringlerini inceledikden sonra gerekli move
// işlemini yapar ve registerları(r1 ,r2 ,r3 ,r4 ,r5) günceller.
// Eğer taşıma işlemini yapamassa false return eder.
bool prnt(string txt , int regArr[] , int size ,const int memArr[] ,int size2);
// Bu fonksiyon verilen txt stringini inceler ve eğer registersa registerın
// degerini , eğer constant deger se dırek o degeri ekrana basar.
// Eğer print işlemini yapamassa false return eder.
bool subOrAdd
(string txt,string txt2,int regArr[],int size,int memArr[],int size2,int value);
//Bu fonksiyon txt ve txt2 stringlerini inceledikden sonra gerekli toplama
// veya çıkarma işlemini value (-1 or +1) değerine göre yapar.
// Value 1 ise toplama , -1 ise çıkarma işlemi yapar.
// Eğer gerekli işlemini yapamassa false return eder.

int main(int argc , char *argv[]){
    const int MEM_SIZE = 50;//memory adındaki arrayin boyutu.
    ifstream cpuFile; //Dosya üzerinden işlem yapmamız için gerekli olan object
    int reg[] = {0,0,0,0,0} , memory[MEM_SIZE];
    // Register ların ilk değerleri.
    int option = convertStrToInt(argv[2]);
    //programı calıştırırken verilen çalıştırma komutunu integer yapıp optiona
    //atadım.

    //memory arrayinin indexleri ne ilk olarak sıfır atanır.
    for(int i = 0 ; i < MEM_SIZE ; ++i)
        memory[i] = 0;

    int line = calculateNumOfline(cpuFile , argv[1]);
    if(line < 0)//fonksiyon sadece dosya olmadıgı zamanlarda - deger return eder
        cerr <<endl<< "That file could not found!!";

    //Talimatları gerçekleştirmek için dosya tekrar açılıyor.
    cpuFile.open(argv[1]);
    switch(option){// option kontrolü.
        case 0:
            if(!option0(cpuFile , line , memory ,MEM_SIZE,reg ,SIZE , argv[1]))
                return -1;
            break;
        case 1:
        case 2:
        	//option0 fonksiyonu ile benzer işlemleri yapıyor artı olarak
        	// ekrana register veya memori yi bastırılıyor girilen optiona göre.
            if(!option12
             (cpuFile , line , memory ,MEM_SIZE , reg , SIZE ,argv[1] , option))
                return -1;
            break;
        default :
            // error mesajı verilir ve program bitirilir eger belitilmemiş
            //command girilmiş ise.
            cerr <<endl<< "Command Error!!"<<endl;
            return -1;
            break;
    }
	cpuFile.close();
    return 0;
}

int option0(ifstream& file , int line , int memArr[] , int memSize ,
				int regArr[] , int regSize , char* fName){

    string mov="MOV",add = "ADD",jmp = "JMP",sub = "SUB";
    string jpn = "JPN",hlt ="HLT",prn = "PRN";
    //Dosyadaki talimatları anlamak için gerekli stringler.(karşılaştırma)
    string text , str ,text2;
    //dosyadan yapılan okumalarda alınan stringerin atanacağı stringler.
    bool control;// While dögüsünü kontrol etmek için gerekli.

    //for döngüsü son satıra gelip gelmediğini kontrol ediyor.
    for(int i = 1 ; i <= line  ; ++i){
	file >> text ;
	// dosyadan okunan komutun her harfi büyük hale getiriliyor.
    makeUpper(text);
    //Hlt; komutunu Hlt haline getiriyor yani noktalı virgülü kaldırıyor.
	modifiedHlt(text);
    if(text == mov || text == add || text == sub || text == hlt || text==prn
                       || text == jmp || text == jpn){

		control = true;
        while(control){
        	if(text == mov){
            	getline(file , str);
            	// bütün satır alınıp sub string hale getirilmek
                // için findSubStr fonksiyonuna gonderiliyor.
                findSubStr(text , text2, str);
                //eğer text2 boş ise komutda hata vardır.
                if (text2 == ""){
                	cerr << "SYNTAX ERROR!!"<<endl;
                    return -1 ;
                }
                if(!move(text,text2,regArr , regSize , memArr ,memSize)){
                // move fonksiyonu gerçekleşmiyorsa program bitiriliyor.

                	cerr<< " ERROR!!!"<<endl;
                    return -1;
                }
                control = false ;
            }
            else if(text == prn){
            	getline(file , str);
                findSubStr(text , text2, str);

   	            if(text2 == ""){
 	        	    if(!prnt(text,regArr , regSize , memArr , memSize)){
                    // prnt fonksiyonu gerçekleşmiyorsa program bitiriliyor.
            	        cerr<< " ERROR!!!"<<endl;
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
            	//program bitirilir.Ama ilk önce hlt ın bulunguğu satırı kontrol
            	// eder. Halt komutundan sonra birşey yazılmış mı diye eger
            	// komut yanlız degilse -1 return edilir
    	    	str = "";
                getline(file , str);
    	        findSubStr(text , text2 , str );
                if(text != "" || text2 != ""){
                 	cerr<<"SYNTAX ERROR IN LAST LINE!!"<<endl;
                    return -1;
                }
                /**************************************************/
                //bu kısımda register degerleri ve memorideki
                //degerler ekrana yazılır.
                prntRegAndValuesInMemory(regArr ,regSize,memArr,memSize);
                /**************************************************/
                return 1;
            }
            else if(text == add || text == sub){

      	      int minusOrPlus = (text == add ? 1 : -1);
              // minusOrPlus'a text add 'e eşitse +1 ,değilse -1 atanıyor.

              getline(file , str);
              findSubStr(text , text2, str);
              if (text2 == ""){
              	cerr << "SYNTAX ERROR!!"<<endl;
              	return -1 ;
              }
              if(!subOrAdd
              			(text,text2,regArr,regSize,memArr,memSize,minusOrPlus)){
              	// subOrAdd fonksiyonu gerçekleşmiyorsa program bitiriliyor.
              	cerr << " ERROR!!!"<<endl;
                return -1;
              }
              control = false ;
           }
           else if(text == jmp || text == jpn){

      	     string tempText = text;
             getline(file , str);
             findSubStr(text , text2, str);

             int jmpVal;
    	     if(tempText == jpn)
        	     jmpVal = jpnn(text,regArr , regSize);
             else
                 jmpVal = jump(text,regArr , regSize);
             // text de register varsa , jnp ve jmp için kosullar
             // ugunsa jmpVal'a 1 atanır.

             if(!jump(file, text ,text2 ,fName,jmpVal,i) || i > line){
        	     //jump fonksiyonu gerçekleşmiyorsa program bitiriliyor
               	 cerr << "SYNTAX/LINE ERROR!!!"<<endl;
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
	}
    return 1;
}
int option12(ifstream& file , int line ,int memArr[] , int memSize ,int regArr[]
             ,int regSize , char* fName , int option){

	// Bu fonksiyon option0 fonksiyonu ile aynı işlemleri yapıyor.
	//ek olarak optiona göre memoriyi ve register degerlerinidi ekrana basıyor.


    string mov="MOV",add = "ADD",jmp = "JMP",sub = "SUB";
    string jpn = "JPN",hlt ="HLT",prn = "PRN";
    //Dosyadaki talimatları anlamak için gerekli stringler.(karşılaştırma)
    string text , str ,text2;
    //dosyadan yapılan okumalarda alınan stringerin atanacağı strinler.
    bool control;// While dögüsünü kontrol etmek için gerekli.

    for(int i = 1 ; i <= line ; ++i){
        file >> text ;
        makeUpper(text);
        modifiedHlt(text);
        if(text == mov || text == add || text == sub || text == hlt || text==prn
                       ||   text == jmp || text == jpn){
        	control = true;
            cout << text;
            while(control){
                if(text == mov){
                    getline(file , str);
                    findSubStr(text , text2, str);
                    if (text2 == ""){
                        cout << " "<< text << endl;
                        cerr << "SYNTAX ERROR!!"<<endl;
                        return -1 ;
                    }
                    if(!move(text,text2,regArr,regSize,memArr ,memSize)){
                        cerr <<endl<< " ERROR!!!"<<endl;
                        cout << " "<< text << "," <<text2;
                        return -1;
                    }
                    cout<< " "<< text<<","<< text2;
                    control =  false ;
                }
                else if(text == prn){
                    getline(file , str);
                    findSubStr(text , text2, str);
                    cout <<" "<<text<<endl;

                    if(text2 == ""){
                        if(!prnt(text,regArr ,regSize , memArr ,memSize)){
                            cerr<< " ERROR!!!"<<endl;
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
                    str = "";
                    getline(file , str);
                    findSubStr(text , text2 , str );
                    if(text != "" || text2 != "" ){
                        cout << " "<<text << text2;;
                        cerr<<endl<<"SYNTAX ERROR IN LAST LINE!!"<<endl;
                        return -1;
                    }
                    prntRegAndValuesInMemory(regArr ,regSize,memArr,memSize);
                    return 1;
                }
                else if(text == add || text == sub){
                    int minusOrPlus = (text == add ? 1 : -1);

                    getline(file , str);
                    findSubStr(text , text2, str);
                    if (text2 == ""){
                        cout << " "<< text << endl;
                        cerr << "SYNTAX ERROR!!"<<endl;
                        return -1 ;
                    }
                    if(!subOrAdd
                        (text,text2,regArr,regSize,memArr,memSize,minusOrPlus)){
                        cout << " " << text << "," << text2<<endl;
                        cerr << " ERROR!!!"<<endl;
                        return -1;
                    }
                    cout<< " "<<text<<","<< text2 ;
                    control = false ;
                }
                else if(text == jmp || text == jpn){
                    string tempText = text;
                    getline(file , str);
                    findSubStr(text , text2, str);
                    cout << " " <<text;

                    int jmpVal;
                    if(tempText == jpn)
                        jmpVal = jpnn(text,regArr , regSize);
                    else
                        jmpVal = jump(text,regArr , regSize);

                    if(!jump(file, text,text2,fName,jmpVal,i) || i > line){

                        // jump fonksiyonu gerçekleşmiyorsa program
                        // bitiriliyor.
                        if(text2 != ""){
                            cout << "," << text2 ;
                            cerr <<endl <<"SYNTAX/LINE ERROR!!!"<<endl;
                            return -1;
                        }
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
        prntRegAndValuesInMemory(regArr ,regSize,memArr,memSize ,option);
    }
    return 1;
}
int calculateNumOfline(ifstream& file , char* fName ){
    string buffer;

    //dosya açılır.
    file.open(fName);
    //dosyanın var olup olmadığına bakılıyor eğer yoksa fonsiyon -1 döner.
    if(file.fail())
        return -1;
    //Dosyadaki satır sayısını bulmak için yapılan işlem.
    // dosyanın sonuna kadar dosya satır satır okunuyor.
    int line = 0;
    while(getline(file , buffer)) {line++;}
    file.close();

    return line;
}
void prntRegAndValuesInMemory
(int regArr[] , int size ,int memArr[], int size2 , int command){

	//bu fonksiyon ekrana memory ve registerlarda ki değerleri basıyor.

	string strReg[] ={"R1","R2","R3","R4","R5"};

    if(command != 0)
    	cout << "- ";
    else
        cout << " ";

	if(command == 1){// command 1 ise ekrana her satırdan sonra registerları
					 // yazar.
    	for(int i = 0; i < size ; ++i){
			cout << strReg[i] << "=" << regArr[i];
            if(i != (size - 1))
            	cout<<",";
    	}
	cout << endl <<endl;
	return;
	}

	// diğer durumda ise memory ve registerdaki değerleri basar.
	for(int i = 0; i < size ; ++i){
	    cout << strReg[i] << "=" << regArr[i];
        if(i != (size - 1))
        	cout<<",";
    }
	cout << endl<<endl;

	for(int i = 0 ; i < size2 ; ++i){
    	cout<<'#'<<i<<"="<<memArr[i];
        if(i != (size2 - 1))
	        cout<<",";
    }
    cout<<endl<<endl;
}
bool
move(string txt,string txt2,int regArr[] , int size , int memArr[] , int size2){

    string strReg[] = {"R1","R2","R3","R4","R5"};

    if(isAllNumber(txt2)){
    	//bu koşula ikinci string tamammen rakamdan oluşuyorsa
        //giriliyor ve registerlar update ediliyor txt2 integer a çevrilerek.
        if(txt[0] != '#'){

            if(!controlTxt(txt , strReg , SIZE)){
            //eğer txt belirtilmeyen register ise fonksiyon false return eder.
                cerr << "REGISTER/SYNTAX";
                return false;
            }

            for(int i = 0 ; i < size ; ++i)
                if(txt == strReg[i])
                    regArr[i] = convertStrToInt(txt2);
        }
        else if(txt[0] == '#' && (convertStrToInt(&txt[1]) <= size2))
        // stringlerdeki' # ' işaretini kontrol ederek memory de atamalar olur.
            memArr[convertStrToInt(&txt[1])] = convertStrToInt(txt2);
        else if(txt[0] == '#' && (convertStrToInt(&txt[1]) >= size2)){
        //var olmayan memory ye ulaşmak istenirse memory error hatası olur
        	cerr<< "MEMORY";
        	return false;
        }
    }
    else if(!isAllNumber(txt2) && !isAllNumber(&txt2[1])){
        	cerr<< "SYNTAX";
        	return false;
    }
    else if(controlTxt(txt,strReg,SIZE)&&txt2[0]== '#' &&isAllNumber(&txt2[1])){

        if(convertStrToInt(&txt2[1]) >= size2){
        //var olmayan memory ye ulaşmak istenirse memory error hatası olur
        	cerr<< "MEMORY";
        	return false;
        }

        //memorden register a mov işlemi yapılır.
        for(int i = 0 ; i < size ; ++i)
            if(txt == strReg[i])
        		memArr[convertStrToInt(&txt2[1])] = regArr[i];
    }
    else if(controlTxt(txt2,strReg,SIZE)&&txt[0]== '#' &&isAllNumber(&txt[1])){

        if(convertStrToInt(&txt[1]) >= size2){
        	cerr<< "MEMORY";
        	return false;
        }
        //registerdan memorye mov işlemi yapılır.
        for(int i = 0 ; i < size ; ++i)
            if(txt2 == strReg[i])
        		regArr[i] = memArr[convertStrToInt(&txt[1])];
    }
    else if(controlTxt(txt , strReg , SIZE) && controlTxt(txt2, strReg ,SIZE)){
        //ikiside register ise gerekli move islemi yapılır.
    	for(int i = 0 ; i < size ; ++i)
            for(int j = 0 ; j < size ; ++j)
    			if(txt == strReg[i] && txt2 == strReg[j])
            		regArr[j] = regArr[i];
    }
    else{
        cerr << "SYNTAX";
        return false;
    }
    return true;
}
bool prnt(string txt , int regArr[] , int size , const int memArr[] ,int size2){

    string strReg[] = {"R1","R2","R3","R4","R5"};

    //verilen txtnin indexleri tamamen rakam içeriyorsa direk orakam ekrana
    // yazılır aksi taktirde txt nin temsil etdiği regsterın değeri yazılır.
    if(isAllNumber(txt))
        cout << " <" <<convertStrToInt(txt)<< "> " ;
    else if(txt[0] == '#'){
    	//eger memorinin sahip olmadığı yere ulaşılmak istenirse false döner.
    	if(convertStrToInt(&txt[1]) >= size2){
        	cerr<< "MEMORY";
        	return false;
        }
        cout << "<" <<memArr[convertStrToInt(&txt[1])]<< ">" ;
    }
    else{
    	//eger txt de var olmayyan reg varsa hata verip false döner.
        if(!controlTxt(txt , strReg , SIZE)){
        	cerr<< "SYNTAX/REGISTER";
        	return false;
        }

    	for(int i = 0; i < size ; ++i)
            if(txt == strReg[i])
                cout << "<"<<regArr[i] << ">";
    }
    return true;
}
bool subOrAdd
(string txt,string txt2,int regArr[],int size ,int memArr[],int size2,int value)
{
    //bu fonksiyoda da txt ve txt2 stringlerini velirlemek için move
    //fonksiyonunda yapılan işlemler yapılıyor farklı olarak burada
    // value değerine göre çıkarma yada toplama işlemi yapılıyor.
    string strReg[] = {"R1","R2","R3","R4","R5"};

    if(isAllNumber(txt2)){
        if(!controlTxt(txt , strReg , SIZE)){
        	cerr<< "SYNTAX";
        	return false;
        }

    	for(int i = 0 ; i < size ; ++i)
            if(txt == strReg[i])
       		regArr[i] = regArr[i] + (value) * convertStrToInt(txt2);
    }
    else if(!isAllNumber(txt2) && !isAllNumber(&txt2[1])){
       	cerr<< "SYNTAX";
       	return false;
    }
    else if(controlTxt(txt,strReg,SIZE)&&txt2[0] == '#'&&isAllNumber(&txt2[1])){

        if(convertStrToInt(&txt2[1]) >= size2){
        	cerr<< "MEMORY";
        	return false;
        }

        for(int i = 0 ; i < size ; ++i)
    		if(txt == strReg[i])
            	regArr[i] += (value) * memArr[convertStrToInt(&txt2[1])];

    }
    else{
        if(!controlTxt(txt , strReg , SIZE) && !controlTxt(txt2, strReg ,SIZE)){
        	cerr<< "SYNTAX";
        	return false;
        }

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
	//txt yi verilen stringde arar bulursa true döner.
    for(int i = 0; i < size ; ++i)
        if(txt == str[i])
            return true;
    return false;
}
void findSubStr( string& txt , string& txt2, string line){

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

   	// stringlerdeki fazla olan boşlukları siler.
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
    string strReg[] = {"R1","R2","R3","R4","R5"};
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
            currentLine = line - 1;
        }
    }
    else
        ctrl = false;
    return ctrl;
}
int jump(string txt , int regArr[] , int size){
    //Eğer txt stringi bi register'ı temsil ediyorsa ve registerın değeri sıfır
    // ise 1(jump yapabilir) değerini return eder.
    string strReg[] = {"R1","R2","R3","R4","R5"};
    bool ctrl = false;

    for(int i = 0 ; i < size ; ++i){
    	if(txt == strReg[i] && regArr[i] == 0)
    		ctrl = true;
    }
    if(ctrl)
    	return 1;
    return 0;
}
int jpnn(string txt , int regArr[] , int size){
    //Eğer txt stringi bi register'ı temsil ediyorsa ve registerın değeri sıfır
    // veya sıfırdan küçükse 1(jump yapabilir) değerini return eder.
    string strReg[] = {"R1","R2","R3","R4","R5"};
    bool ctrl = false;

    for(int i = 0 ; i < size ; ++i){
    	if(txt == strReg[i] && regArr[i] <= 0)
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
