#pragma once

//interface Iexibivel
class IExibivel {
public:
    //destruidor
    virtual ~IExibivel() = default;
    
    //método abstrato
    virtual void exibirDetalhes() const = 0;
};
