#!/bin/bash

(
	cd Entity;
	make;
	./testEntity || exit 1;
) || exit 1

(
	cd Parser;
	make;
	./testParser < ./test.json || exit 1;
) || exit 1

(
	result=0
	cd Parser;
	make;
	echo "{ \"Je suis\" un mauvais Json\": 123.12 aaa }" | ./testParser && result=1;
	./testParser < testFail.json && result=1
	echo "{ \"Je suis un mauvais Json\": 123.12" | ./testParser && result=1;
	exit $result
) || exit 1
