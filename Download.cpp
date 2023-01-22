//
// Created by yonia on 21/01/2023.
//

#include "Download.h"
Download::Download(DefaultIO* dio): Command(dio) {
    description = "download results";
}

void Download::execute(AlgorithmKnn &algorithmKnn) {

}