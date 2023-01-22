//
// Created by yonia on 21/01/2023.
//

#include "Update.h"

Update::Update(DefaultIO *dio): Command(dio) {
    description = "upload an unclassified csv data file";
}

void Update::execute(AlgorithmKnn &algorithmKnn) {

}