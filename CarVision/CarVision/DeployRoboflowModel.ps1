
    $imagePath = "resources/output/temp-img.jpg"
    $api_key = "waYDB2KU5ky1eK8Vid0O"
    $predictionOutput = "resources/output/predictions.json"
	inference infer -i $imagePath -m carvision-7imcs/2 --api-key $api_key | Select-Object -Skip 1 | ForEach-Object { $_ -replace "'", '"' } | Out-File -Encoding ASCII -FilePath "resources/output/predictions.json"

