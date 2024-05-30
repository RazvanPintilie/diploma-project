#pragma once
#include <vector>
#include <string>
#include <cuda_runtime.h>
#include <cudnn.h>
#include "../inc/CocoJsonParser.hpp"

class NeuralNetwork
{
public:
	NeuralNetwork(int numEpochs, float learningRate, int batchSize);
	~NeuralNetwork();

	void Train(const CocoJsonParser& cocoParser);
	std::vector<float> Predict(const std::string& imagePath);

private:
	int numEpochs;
	float learningRate;
	int batchSize;

	cudnnHandle_t cudnn;
	cudnnTensorDescriptor_t inputDesc, outputDesc;
	cudnnFilterDescriptor_t filterDesc;
	cudnnConvolutionDescriptor_t convDesc;

	float* d_input;
	float* d_output;
	float* d_filter;

	void Initialize();
	void Cleanup();
	void Forward(const float* input, float* output);
	void Backward();
	void UpdateWeights();
	std::vector<float> LoadImage(const std::string& imagePath);
};
