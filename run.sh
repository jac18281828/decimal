#!/usr/bin/env bash

VERSION=$(date +%s)

docker build . -t decimal:${VERSION} && \
	docker run --rm -i -t decimal:${VERSION}
