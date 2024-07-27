#include <iostream>
#include <list>
#include <fstream>

int main(int argc, char* argv []) {
    if(argc <= 1) {
        std::printf("Usage: generate_ast <output directory>");
        std::exit(1);
    }

    std::string outputDir = argv[1];

    std::list<std::string> types = {
        "Binary : Expr left, Token operator, Expr right",
        "Grouping : Expr expression",
        "Literal: Object value",
        "Unary : Token operator, Expr right"
    };

    defineAst(outputDir, "Expr", types);
}

class WriterFile{
    public:
        WriterFile(std::string filename): filename(filename) {
            std::ofstream outputfile (filename);

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
        }
        
        void Println(){
            outputfile << "\n";
        }

        void Print(std::string text) {
            outputfile << text;
        }
    
    private:
        std::string filename;
        std::ofstream outputfile;
};


void defineAst(
    std::string outputDir, std::string basename, std::list<std::string> types
) {
   std::string path = outputDir + "/" + basename + ".hpp";
   WriterFile writerFile (path);

   writerFile.Println("ifndef EXPR_H");
   writerFile.Println("#define EXPR_H");
   writerFile.Println("#include \"Token.hpp\"");
   writerFile.Println("class Expr { ");
   writerFile.Println("public:");
   writerFile.Println("virtual ~Expr() = default;");
   writerFile.Println("};");
   writerFile.Println();    


   writerFile.Println("#endif");

}