CC = gcc
CFLAGS = -g -c -Wall
LDFLAGS = -lm -lgmp -O2 -lpthread
CSRC = *.c
HSRC = *.h
OBJS = main.o threads.o algos.o tools.o
EX=crypto

N=402874115778988778181873329071591767722438506891622420041029963578694595240887400867639861461466537103833299413586592359075505942560215384203202392505282949645966546812986702462936795598139258862134305524073117514011710850957577155764134526698071154024866570291655743611106521552616792435986397703408624275326274514077603381064824129105663607213717473307176156322769664543742767983969318459384059938379878060275572931297882085263728828117679720478536475397347975085800596808241438126653968141997207758226940295714228111203845566219741262180987691210467038513314695804493896376930579454464107580662751095564143792253350149446963327062164865068284526946953787948865977316436004163037670156288981621675415729125137439286714883498899856647713325489027165934178641826671600314908207707581913028677627336873027019891101782199420387568674902708563560335665422249993344641004256625323906242830818468942899074234949993913859729756509148940793762235052397899476747243354482142341818566675079971966290454555100106794831122873316939190687807078076069507534444543783013175183099338301868495249460351437732629139146367120478550987016051281632788132605645720897509405100164087829546634973283901954415020317318121023343421442100924240630449162568320542266025029163898709299519931364601129148550918588500543071567482692038979207121165184595857972650794067721766663304877552877530735512541831254657221163688520010481326670262947292075214957731951219393131136071700066722769000670606191390991061973242967512911264351947043296980084166552860987471716618776310267311799281849825634572094586351568980001270007699500229311699965157159517665682831428949194388823813435669597457534867460620737424901559011466473739067552420314197465985734592045469444007987504268282567422361912607903782885199294253733275346340104383835614315889419535761215302433931746650845594336694703703807737307164962815978286100833828641206436538659807846921750141914508632328601539864514384665868751711078980714897238167180581728616753062507511747249245808005997622111641863200180907569048105964570792432318670249656718941478701386677886972338475477550756278048908745855857140396160840915640000152942757067579080105948100791236006113816027294954023517657545229368410211569897436302803253236256834802174708129208380881582322497874260497465180326565377356632463319881488797716878813402070865003833358109311401638399789940308755319571548916779442616446407624398435974737254859567216330307251241356103982692307671884438420399664712045747717349853326279186496926627476702835365616635120395298094996813494640292537645025964806763617960757534317599906545186285779936362239640963157278962749735238734018031963137162294519353089671616839856140612934423376292800357002337948291195231891916319254587638023719991739894135357667509038890693762240291980336551006243082475037374270454634055589954829529267653294431255919681866264708150515182120867007206266224413578578766316288292200080204069908595880864904593530195791992836066271397322016336401432076989173442258953647032430558877151892524852554146167146883853769910561246320694705512457088921711978644056703135770947386634729787650241736975543224255147223770741629765650171444541115341186577164267009666521778404007908942572204437357536447013202320449087374359119884688896570653153635965699349888166816675325403419739923012069285047750708058098369546148066530512705922505763339363973448743551275283628656834670402770338901203538825863885273372725296802331175711226954450363493355782396416901236554095224408448515154810718941778144253019735772286555494888482992676834736600663066924318505506867453994455209613903356661381551303170707697066559694566821068447680650509746035384405738968952295270831628476713602096813200521662297702228641383037720127445077295416522867251086259308924256949130546482529205107067023263892250887651080363021211434271433397608989308330364300732585576535892044008832875413115983363441152995391893368657891779064964168643604233277423002160282408650562356013737533053786211598736805557064344886640795852215801092988641923941455936928232399558235098270821534926531103513400970081240298921105811469814438250610289016969531556231773644918713398451013610901563088260312670567852392406888546913219408585158313060052720828019956940355099824708223899549815719733824216351158321846675607771810334138571606559041577651060598586410945242414351010571013653342029095141793703879402055123962938698179828584589043431623461565217092474712504108095507185137084361406290374948975337884073889633379670194520143162505535982480557240745650789504233993776048710965080738857416484988531003380895803114702386171393470918048735414818380392458071193268641579841938267935481009786061474906992721678353184487194850249990636982112425783667423987765795687026140087895862977235482997376826723315374113237914901333805371711741433497851736832069992653855870002553569186840659098607217033947804144416745928019424098692156435119983976508231816318389379221957628808432933260158025696921301498898560750488043621000694853960738388398663132023687388772635827865444684904043842288121464832536246661065981285950218766526563040447477195329513732641090495498177569836233890464798843005307726003216676981448433911814358187830997562426197639363770484733809493659989183378814319610238163619306208581346901169487332307324999289816374403929506251166966203697910688044201904373375047065577539903412318702343216051705155579477611929334487133386363680801795105965377097317217740629067636115194380331872850516648735434607676631522745733922691440568189717446200213790341992006002410924699429964335507377264900571748863080009435280275806683231919932634328199443166043464046805502904952823468304240431789051431145750174780573029159376608897423116657754646993377252058996584317021186517859545402948554640815812580111812135719244094927777605138918240574534813561862500330654244571788812378520927064783435122985854726038472730062101845156241692016024941211265239314166182038758409312685384765540405212510964896838371037304156419933879530352086544022535109789602027747223650858853482671648101755365481354228091863805011621578883875669404903355089888549376208723682090564341102930475228163313059215959271226081949848477889353337470684677801928746328252980236259643089082064765819268977684271297091434221420402203204816051843790924312901306330991292496802744363898396613407782196679612383549415610569783891526919396336077461916416010666683822481030966646694241533372863428935782537171867644640829719942202233252584945211114561669570501261079454174419086577258210544440106662438203017786099053725933264345420108025868071488561671372008089600018372791881207012696110945775614694650737518542322556296640977293935894214414869438855358753606003397001637907083353780707434779613877126249098033493565718268305571578182703693122089543445743786026405786163677453587602709733484635893390989079294709002676276094965852942303062635499907856117575009515746557862539764756574427752110896827606786025282039152876055050854511817293890036743355523779264511
K=80


interactive: compile
	./$(EX)

.PHONY:run
run: compile 
	./$(EX) $(N) $(K)

valgrind:compile
	valgrind --leak-check=full --show-leak-kinds=all ./$(EX) $(N) $(K)

time: compile
	time ./$(EX) $(N) $(K)

compile:$(OBJS)
	$(CC) -g -o $(EX) $^ $(LDFLAGS)

%.o:%.c %.h
	$(CC) $(CFLAGS) $<

%.o:%.c
	$(CC) $(CFLAGS) $<



DOSSIER = DJEBLAHI_Ahmed_EJJED_Zakaria
FILES = README.md Makefile
.PHONY: zip
zip:
	rm -rf $(DOSSIER)
	rm -f $(DOSSIER).zip
	mkdir $(DOSSIER)
	cp *.c *.h $(FILES) $(DOSSIER)
	zip -r $(DOSSIER).zip $(DOSSIER)
	rm -rf $(DOSSIER)
	ls -l

.PHONY:clean
clean:
	rm -r *.o
	rm -r $(EX)
	ls -l
