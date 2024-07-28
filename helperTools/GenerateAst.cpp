#include <iostream>
#include <list>
#include <vector>
#include <fstream>

void defineAst(std::string, std::string, std::string, std::list<std::string>);

int main(int argc, char* argv []) {
    if(argc <= 2) {
        std::printf("Usage: generate_ast <output directory hpp> <output directory cpp>\n");
        std::exit(1);
    }

    std::string outputDir = argv[1];
    std::string outputDir2 = argv[2];

    std::list<std::string> types = {
        "Binary | Expr left, Token oper, Expr right",
        "Grouping | Expr expression",
        "Literal | std::any value",
        "Unary | Token oper, Expr right"
    };

    defineAst(outputDir, outputDir2, "Expr", types);
}


std::vector<std::string> split_string(std::string str, char delimeter) {
    std::vector<std::string> result;
    int start = 0;
    for(int current = 1; current<str.size(); current++) {
        if(str[current] == delimeter){
             result.push_back(str.substr(start, current - start));
             start = current+1;
        }
    }
    std::string last_split = str.substr(start, str.size() - start);
    if(last_split != "")
        result.push_back(last_split);
    return result;
}

std::string strip_string(std::string& str){
    int start {0}, end = str.size() - 1;
    while(str[start] == ' '){
        start++;
    }
    while(str[end] == ' '){
        end--;
    }
    return str.substr(start, end-start+1);
}


class WriterFile{
    public:
        WriterFile(std::string filename): filename(filename), outputfile(filename) {
        if(!outputfile.is_open()){
            std::cerr << "failed to open the file " << filename <<"\n";
            exit(EXIT_FAILURE);
            }
        }

        ~WriterFile() {
            if(outputfile.is_open()) {
                outputfile.close();
            }
        }

        void Println(std::string text) {
            outputfile << text << "\n";
            outputfile.flush();
        }
        
        void Println(){
            outputfile << "\n";
            outputfile.flush();
        }

        void Print(std::string text) {
            outputfile << text;
            outputfile.flush();
        }
    
    private:
        std::string filename;
        std::ofstream outputfile;
};


void defineType(
    WriterFile& writer,
    WriterFile& writerCpp,
    std::string baseName, 
    std::string className, 
    std::string fields)
    {
        writer.Println("class " + className + ": public " + baseName + "{ ");
        writer.Println("public:");
        
        //split the fieldList
        std::vector<std::string> fieldList = split_string(fields, ',');
        for(std::string field: fieldList) {
            writer.Println("const " + strip_string(field) + ";");              
       }

        writer.Print(className + "(" );
        for(std::string field: fieldList) {
            writer.Print(strip_string(field));
            if(field != fieldList.back()){
                 writer.Print(", ");
            }            
        }
        writer.Println(");");

        writer.Println("};");
        writer.Println();

        //For cpp file
        writerCpp.Print(className+"::"+className+"(");
        for(std::string field: fieldList) {
            writerCpp.Print(strip_string(field));
            if(field != fieldList.back()){
                 writerCpp.Print(", ");
            }            
        }

        writerCpp.Println("): ");

        for(std::string field: fieldList) {
            std::vector<std::string> split = split_string(field, ' ');

            writerCpp.Print(strip_string(split[1])+"("+strip_string(split[1])+")");
            if(field != fieldList.back()){
                writerCpp.Print(", ");
            }
            
        }
        writerCpp.Println(" { }");
        writerCpp.Println();

    }

void defineAst(
    std::string outputDir, std::string outputDirCpp, 
    std::string basename, std::list<std::string> types
) {
   std::string path = outputDir + "/" + basename + ".hpp";
   std::string pathCpp = outputDirCpp + "/" + basename + ".cpp";
   WriterFile writerFileHeader (path);
   WriterFile writerFileCpp (pathCpp);

   writerFileHeader.Println("#ifndef EXPR_H");
   writerFileHeader.Println("#define EXPR_H");
   writerFileHeader.Println("#include \"Token.hpp\"");
   writerFileHeader.Println();
   //TODO: Add all the classes
   //TODO: Add Visitor

   writerFileHeader.Println("class " + basename + " { ");
   writerFileHeader.Println("public:");
   writerFileHeader.Println("virtual ~Expr() = default;");
   //TODO: Add accept virtual method for others to implement   
   writerFileHeader.Println("};");
   writerFileHeader.Println();    

   //for cpp file
   writerFileCpp.Println("#include \""+basename+".hpp\"");
   writerFileCpp.Println();

   for(std::string type: types) {
        std::vector<std::string> splitted_types = split_string(type, '|');
        std::string className =  strip_string(splitted_types[0]);
        std::string fields = strip_string(splitted_types[1]);
        defineType(writerFileHeader, writerFileCpp, basename, className, fields);
   }
    
   writerFileHeader.Println("#endif");

}
