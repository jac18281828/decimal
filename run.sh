#!/usr/bin/env bash

VERSION=$(date +%m%d%y)

docker build . -t decimal:${VERSION} && \
	docker run --rm -i -t decimal:${VERSION}
