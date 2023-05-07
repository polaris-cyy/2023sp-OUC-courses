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
		cout << "文件不存在" << path << endl;
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

//初始化dict，dict[key]为key编码后的值 
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
        printf("无法打开文件%s\n", out_path );
        exit(1);
    }
    ifstream in(in_path);
	if(!in){
		printf("无法打开文件%s\n",in_path );
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

/*将ch转换为二进制string*/ 

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
/***读取配置文件(bushi)***/ 
    ifstream in(fin,ios_base::binary);
    if (in.fail()){
        cout << "无法打开" << fin << endl;
        exit(1);
    }
    //要以文本文件形式打开并写入输出文件，不然回车换行不能正常显示
    ofstream out(fout,ios_base::trunc);
    if (out.fail()){
        cerr << "无法打开" << fout << endl;
        exit(1);
    }
    map<string,char> s2c;
    int size;
    char key;
    char h;
    string value;
    //如果只是>>这种的话，会读取不到\n，然后会出错
    in >> size;
    in.get(h); //读取掉空格
    while(size>0)
    {
        in.get(key); //读取key
        in >> value;  //读取value
        in.get(h);  //读取掉空格
        s2c[value] = key; //将key与value写入s2c
        size--;
    }
//2、开始译码
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
            in.get(c);  //读取每一个char
            if(!in.eof()){//读取到文件末尾时起效，保证读取正常
                c1 = (unsigned char)c;  //转成无符号的
                sc += turnachar(c1);  //转化成原本的二进制串
                length = sc.length();
            }
            //            end = fgetc(in);
        }
        // cerr<<length<<endl<<sc<<endl;
        //当文件结束时，去除补的0及记录个数的char
        if(in.fail()){
            int num = (int)c;  //num代表补0个数
            sc = sc.substr(0,sc.length()-8-num);
        }
        string ss = "";
        int i = 1;
        bool check = false;
        while(sc.length()>0)
        {
            //开始解码
            ss = sc.substr(0,i);
            while(s2c.find(ss) == s2c.end()) //假如在Huffman表中找不到，继续读取下一位
            {
                i++;
                length = sc.length();
                //判断是否超过原字符串大小，避免报错
                if(i>length){
                    check = true;
                    break;
                }
                ss=sc.substr(0,i);
            }
            //用于退出两层循环
            if(check==true){
                break;
            }
            //解码
            result += s2c[ss];
            //去除已解码的部分，继续解码
            sc = sc.substr(i,sc.length()-i);
            i = 1;
        }
        //将解码后的结果写入文件
        out << result;
        //cerr<<"已经进行一个阶段"<<endl;
        //end = fgetc(in);
    }
    in.close();
    out.close();
}

/******************************************************/
/*Pipeline*/

void Encoder(char in_path[], char out_path[]) {
	SymbolCount(in_path); 	//计算频率 
	InitQueue(); 	//创建优先队列 pq 
	GetHuffman();	//创建Huffman树，存在pq.top() 
	InitDict("", pq.top());	//记录下key和value 
	Encode(in_path, out_path);	//保存文件 
}


void Decoder(char in_path[], char out_path[]){
	string result = Decode(in_path, out_path);
	cout << result;
}

/******************************************************/

/******************************************************/
/*将字符串哈夫曼编码并输出。*/

void Count(string str) {
	for (int i = 0; i < str.size(); ++i) {
		m[str.substr(i,1)] += 1;
	}
}

void Str2Huffman() {
	string str;
	cout << "输入字符串";
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
	cout << "选择操作" << endl;
	cout << "1.压缩 2.解码 3.输出一个字符串的哈夫曼编码" << endl; 
	cin >> choice;
	if (choice == 3) {
		Str2Huffman();
		return;
	}
	char in_path[1000], out_path[1000];
	cout << "输入源文件路径" << endl;
	cin >> in_path;
	cout << "输入输出文件路径" << endl;
	cin >> out_path;
	if (choice == 1) {
		Encoder(in_path, out_path);
	} else if (choice == 2) {
		Decoder(in_path, out_path);
	} else {
		cout << "非法操作";
		exit(1);
	}
}

int main() {
	Decision();
	return 0;
} 
