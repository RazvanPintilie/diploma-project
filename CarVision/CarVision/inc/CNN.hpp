#pragma once
#include <torch/torch.h>

class Net : public torch::nn::Module 
{
public:
    Net();

    torch::Tensor forward(torch::Tensor x);

private:
    torch::nn::Conv2d conv1{ nullptr }, conv2{ nullptr };
    torch::nn::Linear fc1{ nullptr }, fc2{ nullptr };
};


