# Installation
## Build docker image
For docker container on cpu only

```
docker build -t konbini_cpu -f ./dockers/cpu.Dockerfile .
```

For docker with gpu
```
docker build -t konbini_gpu -f ./dockers/gpu.Dockerfile .
```

## Build docker container
docker run --rm --gpus=all -it --name konbini_gpu_ctn --shm-size=8G  -e NVIDIA_DRIVER_CAPABILITIES=compute,utility,video,graphics -e CHECK_DUPLICATE=0 --volume="$PWD:/workspace/" -w /workspace/ --network host konbini_gpu bash