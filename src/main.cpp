#include <cstring>
#include "util.hpp"

using namespace bt;

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  notation_t prefix = readFile(file_prefix_in);
  notation_t postfix = readFile(file_postfix_in);

  check_dir(file_out_dir);

  std::fstream fs = openFile(file_aval_out);

  notation_t prefix_from_tree;
  notation_t postfix_from_tree;
  notation_t infix_from_tree;

  if(argc > 1 && (strcmp(argv[1], "--verbose") or strcmp(argv[1], "-v"))) {

    for (std::string expression : postfix){
      BinTree* binTree = new BinTree();
      binTree->from_postfix(binTree->getRoot(), expression);
      binTree->print(binTree->getRoot());

      cout << "Original String:\t" << expression << endl;

      cout << "Posfix notation:\t" << binTree->to_postfix(binTree->getRoot()) << endl;
      prefix_from_tree.push_back(binTree->to_postfix(binTree->getRoot()));

      cout << "Prefix notation:\t" << binTree->to_prefix(binTree->getRoot()) << endl;
      postfix_from_tree.push_back(binTree->to_prefix(binTree->getRoot()));

      cout << "Infix notation: \t" << binTree->to_infix(binTree->getRoot()) << endl;
      infix_from_tree.push_back(binTree->to_infix(binTree->getRoot()));

      cout << "Result: \t" <<  calculator(binTree->to_postfix(binTree->getRoot())) << endl;
      fs << calculator(binTree->to_postfix(binTree->getRoot())) << "\n";
      delete binTree;

    }
    std::cout << "_________________________________" << std::endl;
  }

  else {
    for (std::string expression : postfix){
      BinTree* binTree = new BinTree();
      binTree->from_postfix(binTree->getRoot(), expression);

      postfix_from_tree.push_back(binTree->to_postfix(binTree->getRoot()));

      prefix_from_tree.push_back(binTree->to_prefix(binTree->getRoot()));

      infix_from_tree.push_back(binTree->to_infix(binTree->getRoot()));

      fs << calculator(binTree->to_postfix(binTree->getRoot())) << "\n";
      delete binTree;
    }
  }

  writeFile(prefix_from_tree, file_prefix_out);
  writeFile(postfix_from_tree, file_postfix_out);
  writeFile(infix_from_tree, file_infix_out);

  fs.close();

  return 0;
}
