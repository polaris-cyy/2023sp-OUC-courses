#include <iostream>
#include <fstream>
#include <queue>
#include <cstring>
#include <cstdlib>
#include <string>
#include <map>
#include <bitset>
using namespace std;



map<string, int> m;	//symbol2count
map<string, string> dict;	//coding
map<string, string>::iterator it;

void SymbolCount(char path[]) {
	char ch;
	string s;
	ifstream in(path);
	if (!in) {
		cout << "�ļ�������" << path << endl;
		exit(1);
	}
	while (!in.eof()) {
		in.get(ch);
		if (!in.eof()){
			s = ch;
			m[s] += 1;
		}
	}
}

typedef struct HuffmanNode {
	int weight;
	string symbol;
	HuffmanNode* lchild, *rchild;
	
	HuffmanNode(string s, int w) {
		symbol = s;
		weight = w;
		lchild = rchild = NULL;
	}
}Node, *HFMTree;

class Compare {
	public:
		bool operator()(HFMTree& t1, HFMTree&t2) {
			return t1->weight > t2->weight;
		}
};
priority_queue <HFMTree, vector<HFMTree>, Compare> pq;

void InitQueue() {
	for (map<string, int>::iterator it = m.begin(); it != m.end(); it++) {
		HFMTree node = new Node(it->first, it->second);
		pq.push(node);
	}
}

void GetHuffman() {
	while (pq.size() > 1) {
		HFMTree t1 = pq.top();
		pq.pop();
		HFMTree t2 = pq.top();
		pq.pop();
		string key = t1->symbol + t2->symbol;
		int value = t1->weight + t2->weight;
		HFMTree t = new Node(key, value);
		t->lchild = t1;
		t->rchild = t2;
		pq.push(t);
	}
}

//��ʼ��dict��dict[key]Ϊkey������ֵ 
void InitDict(string code, HFMTree t) {
	if (!t || t->symbol == "") {
		return;
	}
	if (t->symbol.length() == 1) {
		dict[t->symbol] = code;
		//DEBUGING
		cout << t->symbol << ": " << code << " " << endl;
	} else {
		InitDict(code+"0",t->lchild);
		InitDict(code+"1",t->rchild);
	}
}


void Encode(char in_path[], char out_path[])
{
    ofstream out(out_path, ios::trunc|ios::binary);
    if(!out) {
        printf("�޷����ļ�%s\n", out_path );
        exit(1);
    }
    ifstream in(in_path);
	if(!in){
		printf("�޷����ļ�%s\n",in_path );
        return ;
    }
    
    out<<dict.size()<<" ";
    for(it = dict.begin(); it != dict.end(); it++)
    {
        if(it->first.c_str()[0]=='\n'){
            out<<endl;
        }
        out << it->first.c_str() <<it->second.c_str() <<" ";
    }
    
    char ch;
    string s;
    string cs="";
    int length=cs.length();
    string str="";
    unsigned char byte;
    unsigned long temp;
    while(!in.eof())
    {
        while(!in.eof()){
            in.get(ch);
            if(!in.eof()){
                s = ch;
                cs += dict[s];
                length = cs.length();
            }
        }
        while(length >= 8)
        {
            str = cs.substr(0,8);
            bitset<8> bits(str);
            temp = bits.to_ulong();
            byte = temp;
            out << byte;
            cs = cs.substr(8, length-8);
            length = cs.length();
        }
    }
    
    if(length!=0)
    {
        str = cs.substr(0, length);
        int n = 0;
        while(n<8-length)
        {
            str += '0';
            n++;
        }
        bitset<8> bits(str);
        temp=bits.to_ulong();
        byte=temp;
        out<<byte;
    }
    char p = (char)(8-length)%8;
    out << p;
    out.close();
    in.close();
}

/*��chת��Ϊ������string*/ 

string turnachar(unsigned char ch) {
	string k = "";
	int j = 128;
	for (int i = 0; i < 8; ++i) {
		k += (unsigned char)(bool)(ch&j)+'0';
		j >>= 1;
	}
	return k;
} 

string Decode(char fin[], char fout[]) {
/***��ȡ�����ļ�(bushi)***/ 
    ifstream in(fin,ios_base::binary);
    if (in.fail()){
        cout << "�޷���" << fin << endl;
        exit(1);
    }
    //Ҫ���ı��ļ���ʽ�򿪲�д������ļ�����Ȼ�س����в���������ʾ
    ofstream out(fout,ios_base::trunc);
    if (out.fail()){
        cerr << "�޷���" << fout << endl;
        exit(1);
    }
    map<string,char> s2c;
    int size;
    char key;
    char h;
    string value;
    //���ֻ��>>���ֵĻ������ȡ����\n��Ȼ������
    in >> size;
    in.get(h); //��ȡ���ո�
    while(size>0)
    {
        in.get(key); //��ȡkey
        in >> value;  //��ȡvalue
        in.get(h);  //��ȡ���ո�
        s2c[value] = key; //��key��valueд��s2c
        size--;
    }
//2����ʼ����
    char c;
    unsigned char c1;
    string sc = "", result = "";
    int length = sc.length();
    //    int end = fgetc(&in);
    while(!in.fail())
    {
        sc.clear();
        result.clear();
        length = sc.length();
        while(!in.eof()){
            in.get(c);  //��ȡÿһ��char
            if(!in.eof()){//��ȡ���ļ�ĩβʱ��Ч����֤��ȡ����
                c1 = (unsigned char)c;  //ת���޷��ŵ�
                sc += turnachar(c1);  //ת����ԭ���Ķ����ƴ�
                length = sc.length();
            }
            //            end = fgetc(in);
        }
        // cerr<<length<<endl<<sc<<endl;
        //���ļ�����ʱ��ȥ������0����¼������char
        if(in.fail()){
            int num = (int)c;  //num����0����
            sc = sc.substr(0,sc.length()-8-num);
        }
        string ss = "";
        int i = 1;
        bool check = false;
        while(sc.length()>0)
        {
            //��ʼ����
            ss = sc.substr(0,i);
            while(s2c.find(ss) == s2c.end()) //������Huffman�����Ҳ�����������ȡ��һλ
            {
                i++;
                length = sc.length();
                //�ж��Ƿ񳬹�ԭ�ַ�����С�����ⱨ��
                if(i>length){
                    check = true;
                    break;
                }
                ss=sc.substr(0,i);
            }
            //�����˳�����ѭ��
            if(check==true){
                break;
            }
            //����
            result += s2c[ss];
            //ȥ���ѽ���Ĳ��֣���������
            sc = sc.substr(i,sc.length()-i);
            i = 1;
        }
        //�������Ľ��д���ļ�
        out << result;
        //cerr<<"�Ѿ�����һ���׶�"<<endl;
        //end = fgetc(in);
    }
    in.close();
    out.close();
}

/******************************************************/
/*Pipeline*/

void Encoder(char in_path[], char out_path[]) {
	SymbolCount(in_path); 	//����Ƶ�� 
	InitQueue(); 	//�������ȶ��� pq 
	GetHuffman();	//����Huffman��������pq.top() 
	InitDict("", pq.top());	//��¼��key��value 
	Encode(in_path, out_path);	//�����ļ� 
}


void Decoder(char in_path[], char out_path[]){
	string result = Decode(in_path, out_path);
	cout << result;
}

/******************************************************/

/******************************************************/
/*���ַ������������벢�����*/

void Count(string str) {
	for (int i = 0; i < str.size(); ++i) {
		m[str.substr(i,1)] += 1;
	}
}

void Str2Huffman() {
	string str;
	cout << "�����ַ���";
	cin >> str;
	Count(str);
	InitQueue();
	GetHuffman();
	InitDict("", pq.top());
	for (int i = 0; i < str.size(); ++i) {
		cout << dict[str.substr(i,1)];
	}
}

/******************************************************/

void Decision() {
	int choice = 0;
	cout << "ѡ�����" << endl;
	cout << "1.ѹ�� 2.���� 3.���һ���ַ����Ĺ���������" << endl; 
	cin >> choice;
	if (choice == 3) {
		Str2Huffman();
		return;
	}
	char in_path[1000], out_path[1000];
	cout << "����Դ�ļ�·��" << endl;
	cin >> in_path;
	cout << "��������ļ�·��" << endl;
	cin >> out_path;
	if (choice == 1) {
		Encoder(in_path, out_path);
	} else if (choice == 2) {
		Decoder(in_path, out_path);
	} else {
		cout << "�Ƿ�����";
		exit(1);
	}
}

int main() {
	Decision();
	return 0;
} 
