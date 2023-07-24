
#include <Replicator.hpp>


Replicator::Replicator              (){}

Replicator::~Replicator             (){}


void Replicator::copy               (){
    
    for (const auto & entry : filesystem::directory_iterator(src_path)){
        std::cout << entry.path() << std::endl;
    }
    cout << "~~~~~~~~~~" << endl;
}

void Replicator::gep_paths          (Parser* const _p){
    src_path.append(_p->get_src_path());
    rep_path.append(_p->get_rep_path());
}