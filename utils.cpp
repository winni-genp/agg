#include "utils.h"
using namespace std;

int *zeros(int n) {
    int * ret = new int[n];
    for(int i = 0; i < n; i++) ret[i] = 0;
    return(ret);
}

bool fileexists(const string& fname){
    ifstream ifile(fname.c_str());
    return ifile;
}

string percent(int num, int den) {
    char buffer[100];
    sprintf(buffer, "%d / %d\t( %.4f%% )\t", num, den, 100. * float(num) / float(den));
    return(buffer);
}

/*void die(const string& s) {
    cerr << "ERROR: " << s << "\nExiting..." << endl;
    exit(1);
}*/

int strsplit(const string& input, const char split, vector<string> & out) {
    istringstream ss(input);
    out.clear();
    string tmp;
    int count=0;
    while(std::getline(ss, tmp, split))  {
        out.push_back(tmp);    
        count++;
    }
    return(count);
}

string join(const vector<string>& input, const string& delim) {
    string ret = input[0];
    for(int i=1;i<input.size();i++) {
        ret += ",";
        ret += input[i];
    }
    return(ret);
}

vector<int> match(const vector<string>& x, const vector<string>& y) {
    vector<int> ret;
    for(int i = 0; i < y.size(); i++) {
        int j = 0;
        while(x[j] != y[i]) {
            j++;
            if(j >= x.size()) {
                die("sample in y is not in x");
            }
        }
        ret.push_back(j);
    }
    return(ret);
}

/*void warn(const string& s)  {
    cerr << "WARNING: "<<s<<endl;
}*/

//open bcf/vcf for writing.
htsFile *vcf_wopen(const string& out_filename, string output_type) {
  string modew = "w" + output_type;
  cerr << "modew="<<modew<<endl;
  return(hts_open(out_filename.c_str() ? out_filename.c_str() : "-", modew.c_str()));
}

//returns the ##contig=<ID=chr19,length=59128983> lines from a bcf/vcf. 
int copyContigs(bcf_hdr_t *src,bcf_hdr_t *dst) {
  vector<string> parseme;
  char *splitme=bcf_hdr_fmt_text(src, 1, NULL);
  strsplit(splitme,'\n',parseme);
  string contigs = "";
  for(int i=0;i<parseme.size();i++)
    if(parseme[i].find("contig")<parseme[i].size())
      bcf_hdr_append(dst,parseme[i].c_str());
      //      contigs += parseme[i] + "\n";
  free(splitme);
  return(0);
}

int readTextFile(char *fname,vector<string> & output) {
  ifstream ifile(fname);
  if(!ifile)
    die("problem opening" +( (string)fname) );
  string tmp;
  output.clear();
  while(ifile>>tmp) 
    output.push_back(tmp);

  return(output.size());
}
