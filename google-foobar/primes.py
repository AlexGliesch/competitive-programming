def solution(i):
    primes = "2357111317192329313741434753596167717379838997101103107109113127131137139149151157163167173179181191193197199211223227229233239241251257263269271277281283293307311313317331337347349353359367373379383389397401409419421431433439443449457461463467479487491499503509521523541547557563569571577587593599601607613617619631641643647653659661673677683691701709719727733739743751757761769773787797809811821823827829839853857859863877881883887907911919929937941947953967971977983991997100910131019102110311033103910491051106110631069108710911093109711031109111711231129115111531163117111811187119312011213121712231229123112371249125912771279128312891291129713011303130713191321132713611367137313811399140914231427142914331439144714511453145914711481148314871489149314991511152315311543154915531559156715711579158315971601160716091613161916211627163716571663166716691693169716991709172117231733174117471753175917771783178717891801181118231831184718611867187118731877187918891901190719131931193319491951197319791987199319971999200320112017202720292039205320632069208120832087208920992111211321292131213721412143215321612179220322072213222122372239224322512267226922732281228722932297230923112333233923412347235123572371237723812383238923932399241124172423243724412447245924672473247725032521253125392543254925512557257925912593260926172621263326472657265926632671267726832687268926932699270727112713271927292731274127492753276727772789279127972801280328192833283728432851285728612879288728972903290929172927293929532957296329692971299930013011301930233037304130493061306730793083308931093119312131373163316731693181318731913203320932173221322932513253325732593271329933013307331333193323332933313343334733593361337133733389339134073413343334493457346134633467346934913499351135173527352935333539354135473557355935713581358335933607361336173623363136373643365936713673367736913697370137093719372737333739376137673769377937933797380338213823383338473851385338633877388138893907391139173919392339293931394339473967398940014003400740134019402140274049405140574073407940914093409941114127412941334139415341574159417742014211421742194229423142414243425342594261427142734283428942974327433743394349435743634373439143974409442144234441444744514457446344814483449345074513451745194523454745494561456745834591459746034621463746394643464946514657466346734679469147034721472347294733475147594783478747894793479948014813481748314861487148774889490349094919493149334937494349514957496749694973498749934999500350095011502150235039505150595077508150875099510151075113511951475153516751715179518951975209522752315233523752615273527952815297530353095323533353475351538153875393539954075413541754195431543754415443544954715477547954835501550355075519552155275531555755635569557355815591562356395641564756515653565756595669568356895693570157115717573757415743574957795783579158015807581358215827583958435849585158575861586758695879588158975903592359275939595359815987600760116029603760436047605360676073607960896091610161136121613161336143615161636173619761996203621162176221622962476257626362696271627762876299630163116317632363296337634363536359636163676373637963896397642164276449645164696473648164916521652965476551655365636569657165776581659966076619663766536659666166736679668966916701670367096719673367376761676367796781679167936803682368276829683368416857686368696871688368996907691169176947694969596961696769716977698369916997700170137019702770397043705770697079710371097121712771297151715971777187719372077211721372197229723772437247725372837297730773097321733173337349735173697393741174177433745174577459747774817487748974997507751775237529753775417547754975597561757375777583758975917603760776217639764376497669767376817687769176997703771777237727774177537757775977897793781778237829784178537867787378777879788379017907791979277933793779497951796379938009801180178039805380598069808180878089809381018111811781238147816181678171817981918209821982218231823382378243826382698273828782918293829783118317832983538363836983778387838984198423842984318443844784618467850185138521852785378539854385638573858185978599860986238627862986418647866386698677868186898693869987078713871987318737874187478753876187798783880388078819882188318837883988498861886388678887889389238929893389418951896389698971899990019007901190139029904190439049905990679091910391099127913391379151915791619173918191879199920392099221922792399241925792779281928392939311931993239337934193439349937193779391939794039413941994219431943394379439946194639467947394799491949795119521953395399547955195879601961396199623962996319643964996619677967996899697971997219733973997439749976797699781978797919803981198179829983398399851985798599871988398879901990799239929993199419949996799731000710009100371003910061100671006910079100911009310099101031011110133101391014110151101591016310169101771018110193102111022310243102471025310259102671027110273102891030110303103131032110331103331033710343103571036910391103991042710429104331045310457104591046310477104871049910501105131052910531105591056710589105971060110607106131062710631106391065110657106631066710687106911070910711107231072910733107391075310771107811078910799108311083710847108531085910861108671088310889108911090310909109371093910949109571097310979109871099311003110271104711057110591106911071110831108711093111131111711119111311114911159111611117111173111771119711213112391124311251112571126111273112791128711299113111131711321113291135111353113691138311393113991141111423114371144311447114671147111483114891149111497115031151911527115491155111579115871159311597116171162111633116571167711681116891169911701117171171911731117431177711779117831178911801118071181311821118271183111833118391186311867118871189711903119091192311927119331193911941119531195911969119711198111987120071201112037120411204312049120711207312097121011210712109121131211912143121491215712161121631219712203122111222712239122411225112253122631226912277122811228912301123231232912343123471237312377123791239112401124091241312421124331243712451124571247312479124871249112497125031251112517125271253912541125471255312569125771258312589126011261112613126191263712641126471265312659126711268912697127031271312721127391274312757127631278112791127991280912821128231282912841128531288912893128991290712911129171291912923129411295312959129671297312979129831300113003130071300913033130371304313049130631309313099131031310913121131271314713151131591316313171131771318313187132171321913229132411324913259132671329113297133091331313327133311333713339133671338113397133991341113417134211344113451134571346313469134771348713499135131352313537135531356713577135911359713613136191362713633136491366913679136811368713691136931369713709137111372113723137291375113757137591376313781137891379913807138291383113841138591387313877138791388313901139031390713913139211393113933139631396713997139991400914011140291403314051140571407114081140831408714107141431414914153141591417314177141971420714221142431424914251142811429314303143211432314327143411434714369143871438914401144071441114419144231443114437144471444914461144791448914503145191453314537145431454914551145571456114563145911459314621146271462914633146391465314657146691468314699147131471714723147311473714741147471475314759147671477114779147831479714813148211482714831148431485114867148691487914887148911489714923149291493914947149511495714969149831501315017150311505315061150731507715083150911510115107151211513115137151391514915161151731518715193151991521715227152331524115259152631526915271152771528715289152991530715313153191532915331153491535915361153731537715383153911540115413154271543915443154511546115467154731549315497155111552715541155511555915569155811558315601156071561915629156411564315647156491566115667156711567915683157271573115733157371573915749157611576715773157871579115797158031580915817158231585915877158811588715889159011590715913159191592315937159591597115973159911600116007160331605716061160631606716069160731608716091160971610316111161271613916141161831618716189161931621716223162291623116249162531626716273163011631916333163391634916361163631636916381164111641716421164271643316447164511645316477164811648716493165191652916547165531656116567165731660316607166191663116633166491665116657166611667316691166931669916703167291674116747167591676316787168111682316829168311684316871168791688316889169011690316921169271693116937169431696316979169811698716993170111702117027170291703317041170471705317077170931709917107171171712317137171591716717183171891719117203172071720917231172391725717291172931729917317173211732717333173411735117359173771738317387173891739317401174171741917431174431744917467174711747717483174891749117497175091751917539175511756917573175791758117597175991760917623176271765717659176691768117683177071771317729177371774717749177611778317789177911780717827178371783917851178631788117891179031790917911179211792317929179391795717959179711797717981179871798918013180411804318047180491805918061180771808918097181191812118127181311813318143181491816918181181911819918211182171822318229182331825118253182571826918287182891830118307183111831318329183411835318367183711837918397184011841318427184331843918443184511845718461184811849318503185171852118523185391854118553185831858718593186171863718661186711867918691187011871318719187311874318749187571877318787187931879718803188391885918869188991891118913189171891918947189591897318979190011900919013190311903719051190691907319079190811908719121191391914119157191631918119183192071921119213192191923119237192491925919267192731928919301193091931919333193731937919381193871939119403194171942119423194271942919433194411944719457194631946919471194771948319489195011950719531195411954319553195591957119577195831959719603196091966119681196871969719699197091971719727197391975119753197591976319777197931980119813198191984119843198531986119867198891989119913199191992719937199491996119963199731997919991199931999720011200212002320029200472005120063200712008920101201072011320117201232012920143201472014920161201732017720183202012021920231202332024920261202692028720297203232032720333203412034720353203572035920369203892039320399204072041120431204412044320477204792048320507205092052120533205432054920551205632059320599206112062720639206412066320681206932070720717207192073120743207472074920753207592077120"
    return primes[i:i+5]

print(solution(3))