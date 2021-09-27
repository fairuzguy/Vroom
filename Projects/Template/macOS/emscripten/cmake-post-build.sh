#!/bin/bash

cp template.html out/index.html
pushd out
	npx kill-port 8000
	python -m SimpleHTTPServer 8000 & open http://localhost:8000
popd
