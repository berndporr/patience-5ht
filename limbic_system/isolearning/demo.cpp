#include "isolearning.h"
#include <unistd.h>

// flag which switches on the trace flag:
// If this flag is on a trace is generated instead of the
// resonator response for the predictive pathway.
int trace=0;


// Two inputs: reflex and predictor
// Just one filter in the filterbank
// Low learning rate
void isolearningWithOneFilterLow() {
	Isolearning isolearning(2,1);
	isolearning.setLearningRate(0.00001);
	isolearning.setReflex(0.01,0.6);
	if (trace)
		isolearning.setPredictorsAsTraces(50);
	else
		isolearning.setPredictorsAsBandp(0.01,0.6);
	isolearning.openDocu("onef_low");
	for(int step=0;step<150000;step++) {
		if (step%1000==500) {
			isolearning.setInput(1,1);
		} else {
			isolearning.setInput(1,0);
		}
		if ((step%1000==525)&&(step<100000)) {
			isolearning.setInput(0,1);
		} else {
			isolearning.setInput(0,0);
		}
		isolearning.prediction(step);
		isolearning.writeDocu(step);
	}
}




void isolearningWithOneFilterHigh() {
	// Two inputs: reflex and predictor
	// Just one filter in the filterbank
	Isolearning isolearning(2,1);
	isolearning.setLearningRate(0.0001);
	isolearning.setReflex(0.01,0.6);
	if (trace)
		isolearning.setPredictorsAsTraces(50);
	else
		isolearning.setPredictorsAsBandp(0.01,0.6);
	isolearning.openDocu("onef_high");
	for(int step=0;step<150000;step++) {
		if (step%1000==500) {
			isolearning.setInput(1,1);
		} else {
			isolearning.setInput(1,0);
		}
		if ((step%1000==525)&&(step<100000)) {
			isolearning.setInput(0,1);
		} else {
			isolearning.setInput(0,0);
		}
		isolearning.prediction(step);
		if (step%10==0)
			isolearning.writeDocu(step);
	}
}





void isolearningWithOneFilterHighest() {
	// Two inputs: reflex and predictor
	// Just one filter in the filterbank
	Isolearning isolearning(2,1);
	isolearning.setLearningRate(0.005);
	isolearning.setReflex(0.01,0.6);
	if (trace)
		isolearning.setPredictorsAsTraces(50);
	else
		isolearning.setPredictorsAsBandp(0.01,0.6);
	isolearning.openDocu("onef_highest");
	for(int step=0;step<150000;step++) {
		if (step%1000==500) {
			isolearning.setInput(1,1);
		} else {
			isolearning.setInput(1,0);
		}
		if ((step%1000==525)&&(step<100000)) {
			isolearning.setInput(0,1);
		} else {
			isolearning.setInput(0,0);
		}
		isolearning.prediction(step);
		isolearning.writeDocu(step);
	}
}



void isolearningWith10FilterHigh() {
	// Two inputs: reflex and predictor
	// Just one filter in the filterbank
	Isolearning isolearning(2,10);
	isolearning.setLearningRate(0.00025);

	isolearning.setReflex(0.01,0.6);
	if (trace)
		isolearning.setPredictorsAsBandp(0.1,0.6);
	else
		isolearning.setPredictorsAsBandp(0.1,0.6);
	isolearning.openDocu("10filt_high");
	for(int step=0;step<150000;step++) {
		if (step%1000==500) {
			isolearning.setInput(1,1);
		} else {
			isolearning.setInput(1,0);
		}
		if ((step%1000==525)&&(step<100000))
		  {
			isolearning.setInput(0,1);
		  } else {
			isolearning.setInput(0,0);
		}
		isolearning.prediction(step);
		if (step%10==0) {
			isolearning.writeDocu(step);
		}
	}
}




void isolearningWith10FilterHighest() {
	// Two inputs: reflex and predictor
	// Just one filter in the filterbank
	Isolearning isolearning(2,10);
	isolearning.setLearningRate(0.01);
	isolearning.setReflex(0.01,0.6);
	if (trace)
		isolearning.setPredictorsAsTraces(50);
	else
		isolearning.setPredictorsAsBandp(0.1,0.6);
	isolearning.openDocu("10filt_highest");
	for(int step=0;step<150000;step++) {
		if (step%1000==500) {
			isolearning.setInput(1,1);
		} else {
			isolearning.setInput(1,0);
		}
		if ((step%1000==525)&&(step<100000)) {
			isolearning.setInput(0,1);
		} else {
			isolearning.setInput(0,0);
		}
		isolearning.prediction(step);
		if (step%10==0) {
			isolearning.writeDocu(step);
		}
	}
}







void stdpWithOneFilterLow() {
	FILE* f=fopen("stdp_low.dat","wt");
	for(int t=-200;t<=200;t++) {
		Isolearning* isolearning=new Isolearning(2,1);
		isolearning->setLearningRate(0.0001);
		isolearning->setReflex(0.01,0.6);
		if (trace)
			isolearning->setPredictorsAsTraces(50);
		else
			isolearning->setPredictorsAsBandp(0.01,0.6);
		fprintf(stderr,"%d\n",t);
		fflush(stderr);
		for(int step=0;step<5000;step++) {
			if ((step%1000)==500) {
				isolearning->setInput(1,1);
			} else {
				isolearning->setInput(1,0);
			}
			if ((step%1000)==(500+t)) {
				isolearning->setInput(0,1);
			} else {
				isolearning->setInput(0,0);
			}
			isolearning->prediction(step);
		}
		fprintf(f,"%d %f\n",t,isolearning->getWeight(1,0));
		delete isolearning;
	}
	fclose(f);
	fprintf(stderr,"\n");
}











int main(int argc, char *argv[]) {
        int c;
	int demoNumber=-1;

        while (-1 != (c = getopt(argc, argv, "td:"))) {
                switch (c) {
                case 'd':
                        demoNumber = strtoul(optarg,NULL,0);
                        break;

		case 't':
			// switch to trace instead of bandpass
			trace = 1;
			fprintf(stderr,"Filter responses are traces\n");
			break;

		default:
			printf("bad option\n");
			exit(1);
		}
	}

	if (demoNumber<0) {
		fprintf(stderr,"Usage: %s [-d demo_number] [-t]\n",argv[0]);
		fprintf(stderr," Parameters:\n");
		fprintf(stderr," -d 0    one filter in the pred pathway, mu=low\n");
		fprintf(stderr," -d 1    one filter in the pred pathway, mu=high\n");
		fprintf(stderr," -d 2    one filter in the pred pathway, mu=highest\n");
		fprintf(stderr," -d 100  filterbank in the pred pathway, mu=high\n");
		fprintf(stderr," -d 101  filterbank in the pred pathway, mu=highest\n");
		fprintf(stderr," -d 1000 STDP curve with one filter\n");
		fprintf(stderr," -t      pred filters are squ pulse with 50 steps.\n");
		fprintf(stderr,"\n");
		exit(1);
	}

	fprintf(stderr,"Demo #%d\n",demoNumber);
	switch (demoNumber) {
	case 0:
		isolearningWithOneFilterLow();
		break;
	case 1:
		isolearningWithOneFilterHigh();
		break;
	case 2:
		isolearningWithOneFilterHighest();
		break;

	case 100:
		isolearningWith10FilterHigh();
		break;

	case 101:
		isolearningWith10FilterHighest();
		break;

	case 1000:
		stdpWithOneFilterLow();
		break;


	}

}
