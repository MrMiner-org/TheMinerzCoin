#!/usr/bin/env bash
set -euo pipefail
# Build and push Docker images for GitHub builds.

IMAGE_NAME=${IMAGE_NAME:-theminerzcoin}
TAG=${GIT_CURRENT_BRANCH:-latest}

# Build Docker image

docker build -t "${IMAGE_NAME}:${TAG}" -f docker/Dockerfile .

# Push Docker image

docker push "${IMAGE_NAME}:${TAG}"

