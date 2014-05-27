// SLIC.cpp: implementation of the SLIC class.
//
// Copyright (C) Radhakrishna Achanta 2012
// All rights reserved
// Email: firstname.lastname@epfl.ch
//////////////////////////////////////////////////////////////////////


#include "SLIC.h"


void print_klabels(string str, const vector<int>& klabels, int sz)
{
    cout << str << endl;

    for(int i=0; i<sz; i++) {
        cout << klabels.at(i) << endl;
    }
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


SLIC::SLIC()
{
    m_lvec = NULL;
    m_avec = NULL;
    m_bvec = NULL;

    m_lvecvec = NULL;
    m_avecvec = NULL;
    m_bvecvec = NULL;

    m_height = 0;
    m_depth = 0;
    m_width = 0;
}


SLIC::~SLIC()
{
    if(m_lvec) delete [] m_lvec;
    if(m_avec) delete [] m_avec;
    if(m_bvec) delete [] m_bvec;


    if(m_lvecvec)
    {
        for( int d = 0; d < m_depth; d++ ) delete [] m_lvecvec[d];
        delete [] m_lvecvec;
    }
    if(m_avecvec)
    {
        for( int d = 0; d < m_depth; d++ ) delete [] m_avecvec[d];
        delete [] m_avecvec;
    }
    if(m_bvecvec)
    {
        for( int d = 0; d < m_depth; d++ ) delete [] m_bvecvec[d];
        delete [] m_bvecvec;
    }
}

//==============================================================================
///	RGB2XYZ
///
/// sRGB (D65 illuninant assumption) to XYZ conversion
//==============================================================================
void SLIC::RGB2XYZ(
        const int&		sR,
        const int&		sG,
        const int&		sB,
        double&			X,
        double&			Y,
        double&			Z)
{
    double R = sR/255.0;
    double G = sG/255.0;
    double B = sB/255.0;

    double r, g, b;

    if(R <= 0.04045)	r = R/12.92;
    else				r = pow((R+0.055)/1.055,2.4);
    if(G <= 0.04045)	g = G/12.92;
    else				g = pow((G+0.055)/1.055,2.4);
    if(B <= 0.04045)	b = B/12.92;
    else				b = pow((B+0.055)/1.055,2.4);

    X = r*0.4124564 + g*0.3575761 + b*0.1804375;
    Y = r*0.2126729 + g*0.7151522 + b*0.0721750;
    Z = r*0.0193339 + g*0.1191920 + b*0.9503041;
}

//===========================================================================
///	RGB2LAB
//===========================================================================
void SLIC::RGB2LAB(const int& sR, const int& sG, const int& sB, double& lval, double& aval, double& bval)
{
    //------------------------
    // sRGB to XYZ conversion
    //------------------------
    double X, Y, Z;
    RGB2XYZ(sR, sG, sB, X, Y, Z);

    //------------------------
    // XYZ to LAB conversion
    //------------------------
    double epsilon = 0.008856;	//actual CIE standard
    double kappa   = 903.3;		//actual CIE standard

    double Xr = 0.950456;	//reference white
    double Yr = 1.0;		//reference white
    double Zr = 1.088754;	//reference white

    double xr = X/Xr;
    double yr = Y/Yr;
    double zr = Z/Zr;

    double fx, fy, fz;
    if(xr > epsilon)	fx = pow(xr, 1.0/3.0);
    else				fx = (kappa*xr + 16.0)/116.0;
    if(yr > epsilon)	fy = pow(yr, 1.0/3.0);
    else				fy = (kappa*yr + 16.0)/116.0;
    if(zr > epsilon)	fz = pow(zr, 1.0/3.0);
    else				fz = (kappa*zr + 16.0)/116.0;

    lval = 116.0*fy-16.0;
    aval = 500.0*(fx-fy);
    bval = 200.0*(fy-fz);
}

//===========================================================================
///	DoRGBtoLABConversion
///
///	For whole image: overlaoded floating point version
//===========================================================================
void SLIC::DoRGBtoLABConversion(
        const unsigned int*&		ubuff,
        double*&					lvec,
        double*&					avec,
        double*&					bvec)
{
    int sz = m_width*m_height;
    lvec = new double[sz];
    avec = new double[sz];
    bvec = new double[sz];

    for( int j = 0; j < sz; j++ )
    {
        int r = (ubuff[j] >> 16) & 0xFF;
        int g = (ubuff[j] >>  8) & 0xFF;
        int b = (ubuff[j]      ) & 0xFF;

        RGB2LAB( r, g, b, lvec[j], avec[j], bvec[j] );
    }
}


//=================================================================================
/// DrawContoursAroundSegments
///
/// Internal contour drawing option exists. One only needs to comment the if
/// statement inside the loop that looks at neighbourhood.
//=================================================================================
void SLIC::DrawContoursAroundSegments(
        unsigned int*&			ubuff,
        vector<int>&			labels,
        const int&				width,
        const int&				height )
{
    const int dx8[8] = {-1, -1,  0,  1, 1, 1, 0, -1};
    const int dy8[8] = { 0, -1, -1, -1, 0, 1, 1,  1};

    int sz = width*height;
    vector<bool> istaken(sz, false);
    vector<int> contourx(sz);vector<int> contoury(sz);
    int mainindex(0);int cind(0);
    for( int j = 0; j < height; j++ )
    {
        for( int k = 0; k < width; k++ )
        {
            int np(0);
            for( int i = 0; i < 8; i++ )
            {
                int x = k + dx8[i];
                int y = j + dy8[i];

                if( (x >= 0 && x < width) && (y >= 0 && y < height) )
                {
                    int index = y*width + x;

                    //if( false == istaken[index] )//comment this to obtain internal contours
                    {
                        if( labels[mainindex] != labels[index] ) np++;
                    }
                }
            }
            if( np > 1 )
            {
                contourx[cind] = k;
                contoury[cind] = j;
                istaken[mainindex] = true;
                cind++;
            }
            mainindex++;
        }
    }

    int numboundpix = cind;
    for( int j = 0; j < numboundpix; j++ )
    {
        int ii = contoury[j]*width + contourx[j];
        ubuff[ii] = 0xffffff;

        for( int n = 0; n < 8; n++ )
        {
            int x = contourx[j] + dx8[n];
            int y = contoury[j] + dy8[n];
            if( (x >= 0 && x < width) && (y >= 0 && y < height) )
            {
                int ind = y*width + x;
                if(!istaken[ind]) ubuff[ind] = 0;
            }
        }
    }
}


//==============================================================================
///	DetectLabEdges
//==============================================================================
void SLIC::DetectLabEdges(
        const double*				lvec,
        const double*				avec,
        const double*				bvec,
        const int&					width,
        const int&					height,
        vector<double>&				edges)
{
    int sz = width*height;

    edges.resize(sz,0);
    for( int j = 1; j < height-1; j++ )
    {
        for( int k = 1; k < width-1; k++ )
        {
            int i = j*width+k;

            double dx = (lvec[i-1]-lvec[i+1])*(lvec[i-1]-lvec[i+1]) +
                    (avec[i-1]-avec[i+1])*(avec[i-1]-avec[i+1]) +
                    (bvec[i-1]-bvec[i+1])*(bvec[i-1]-bvec[i+1]);

            double dy = (lvec[i-width]-lvec[i+width])*(lvec[i-width]-lvec[i+width]) +
                    (avec[i-width]-avec[i+width])*(avec[i-width]-avec[i+width]) +
                    (bvec[i-width]-bvec[i+width])*(bvec[i-width]-bvec[i+width]);

            //edges[i] = fabs(dx) + fabs(dy);
            edges[i] = dx*dx + dy*dy;
        }
    }
}

//===========================================================================
///	PerturbSeeds
//===========================================================================
void SLIC::PerturbSeeds(
        vector<double>&				kseedsl,
        vector<double>&				kseedsa,
        vector<double>&				kseedsb,
        vector<double>&				kseedsx,
        vector<double>&				kseedsy,
        const vector<double>&                   edges)
{
    const int dx8[8] = {-1, -1,  0,  1, 1, 1, 0, -1};
    const int dy8[8] = { 0, -1, -1, -1, 0, 1, 1,  1};

    int numseeds = kseedsl.size();

    for( int n = 0; n < numseeds; n++ )
    {
        int ox = kseedsx.at(n);//original x
        int oy = kseedsy.at(n);//original y
        int oind = oy*m_width + ox;

        int storeind = oind;
        for( int i = 0; i < 8; i++ )
        {
            int nx = ox+dx8[i];//new x
            int ny = oy+dy8[i];//new y

            if( nx >= 0 && nx < m_width && ny >= 0 && ny < m_height)
            {
                int nind = ny*m_width + nx;
                if( edges[nind] < edges[storeind])
                {
                    storeind = nind;
                }
            }
        }
        if(storeind != oind)
        {
            kseedsx.at(n) = storeind%m_width;
            kseedsy.at(n) = storeind/m_width;
            kseedsl.at(n) = m_lvec[storeind];
            kseedsa.at(n) = m_avec[storeind];
            kseedsb.at(n) = m_bvec[storeind];
        }
    }
}


//===========================================================================
///	GetLABXYSeeds_ForGivenStepSize
///
/// The k seed values are taken as uniform spatial pixel samples.
//===========================================================================
void SLIC::GetLABXYSeeds_ForGivenStepSize(
        vector<double>&				kseedsl,
        vector<double>&				kseedsa,
        vector<double>&				kseedsb,
        vector<double>&				kseedsx,
        vector<double>&				kseedsy,
        const int&					STEP,
        const bool&					perturbseeds,
        const vector<double>&       edgemag)
{
    const bool hexgrid = false;
    int numseeds(0);
    int n(0);

    int xstrips = (0.5+double(m_width)/double(STEP));
    int ystrips = (0.5+double(m_height)/double(STEP));

    int xerr = m_width  - STEP*xstrips;if(xerr < 0 && xstrips > 1){xstrips--;xerr = m_width - STEP*xstrips;}
    int yerr = m_height - STEP*ystrips;if(yerr < 0 && ystrips > 1){ystrips--;yerr = m_height- STEP*ystrips;}

    double xerrperstrip = double(xerr)/double(xstrips);
    double yerrperstrip = double(yerr)/double(ystrips);

    int xoff = STEP/2;
    int yoff = STEP/2;
    //-------------------------
    numseeds = xstrips*ystrips;
    //-------------------------

    kseedsl.resize(numseeds);
    kseedsa.resize(numseeds);
    kseedsb.resize(numseeds);
    kseedsx.resize(numseeds);
    kseedsy.resize(numseeds);

    for( int y = 0; y < ystrips; y++ )
    {
        int ye = y*yerrperstrip;
        for( int x = 0; x < xstrips; x++ )
        {
            int xe = x*xerrperstrip;
            int seedx = (x*STEP+xoff+xe);
            if(hexgrid){ seedx = x*STEP+(xoff<<(y&0x1))+xe; seedx = cv::min(m_width-1,seedx); }//for hex grid sampling
            int seedy = (y*STEP+yoff+ye);
            int i = seedy*m_width + seedx;

            kseedsl.at(n) = m_lvec[i];
            kseedsa.at(n) = m_avec[i];
            kseedsb.at(n) = m_bvec[i];
            kseedsx.at(n) = seedx;
            kseedsy.at(n) = seedy;
            n++;
        }
    }


    if(perturbseeds)
    {
        PerturbSeeds(kseedsl, kseedsa, kseedsb, kseedsx, kseedsy, edgemag);
    }
}


//===========================================================================
///	PerformSuperpixelSLIC
///
///	Performs k mean segmentation. It is fast because it looks locally, not
/// over the entire image.
//===========================================================================
void SLIC::PerformSuperpixelSLIC(
        vector<double>&				kseedsl,
        vector<double>&				kseedsa,
        vector<double>&				kseedsb,
        vector<double>&				kseedsx,
        vector<double>&				kseedsy,
        vector<int>&				klabels,
        const int&				    STEP,
        const double&				M)
{
    int sz = m_width*m_height;
    const int numk = kseedsl.size();

    //----------------
    int offset = STEP;

    //if(STEP < 8) offset = STEP*1.5;//to prevent a crash due to a very small step size
    //----------------

    vector<double> clustersize(numk, 0);
    vector<double> inv(numk, 0);//to store 1/clustersize[k] values

    vector<double> sigmal(numk, 0);
    vector<double> sigmaa(numk, 0);
    vector<double> sigmab(numk, 0);
    vector<double> sigmax(numk, 0);
    vector<double> sigmay(numk, 0);
    vector<double> distvec(sz, DBL_MAX);

    double invwt = 1.0/((STEP/M)*(STEP/M));

    int x1, y1, x2, y2;
    double l, a, b;
    double dist;
    double distxy;

    //print_klabels("Before Loop: ", klabels, sz);
    for( int itr = 0; itr < 10; itr++ )
    {

        distvec.assign(sz, DBL_MAX);

        for( int n = 0; n < numk; n++ )
        {
            //cout << "QQQ" << endl;
            y1 = cv::max(0.0, kseedsy.at(n)-offset);
            y2 = cv::min((double)m_height,	kseedsy.at(n)+offset);
            x1 = cv::max(0.0,			kseedsx.at(n)-offset);
            x2 = cv::min((double)m_width,	kseedsx.at(n)+offset);


            for( int y = y1; y < y2; y++ )
            {
                for( int x = x1; x < x2; x++ )
                {
                    int i = y*m_width + x;

                    l = m_lvec[i];
                    a = m_avec[i];
                    b = m_bvec[i];

                    dist =			(l - kseedsl.at(n))*(l - kseedsl.at(n)) +
                            (a - kseedsa.at(n))*(a - kseedsa.at(n)) +
                            (b - kseedsb.at(n))*(b - kseedsb.at(n));

                    distxy =		(x - kseedsx.at(n))*(x - kseedsx.at(n)) +
                            (y - kseedsy.at(n))*(y - kseedsy.at(n));

                    //------------------------------------------------------------------------
                    dist += distxy*invwt;//dist = sqrt(dist) + sqrt(distxy*invwt);//this is more exact
                    //------------------------------------------------------------------------
                    if( dist < distvec.at(i) )
                    {
                        distvec.at(i) = dist;
                        klabels.at(i)  = n;
                    }
                }
            }
        }


        //-----------------------------------------------------------------
        // Recalculate the centroid and store in the seed values
        //-----------------------------------------------------------------
        //instead of reassigning memory on each iteration, just reset.

        sigmal.assign(numk, 0);
        sigmaa.assign(numk, 0);
        sigmab.assign(numk, 0);
        sigmax.assign(numk, 0);
        sigmay.assign(numk, 0);
        clustersize.assign(numk, 0);
        //------------------------------------
        //edgesum.assign(numk, 0);
        //------------------------------------

        {int ind(0);


        for( int r = 0; r < m_height; r++ )
        {
            for( int c = 0; c < m_width; c++ )
            {
                //cout << "ADDRESS1: " << (klabels+ind)  << " : " << klabels[ind] << endl;
                //cout << sigmal[klabels[ind]] << endl;
                //cout << "ADDRESS2: " << &sigmal[0] << endl;

            	if( klabels.at(ind) < 0 )
            	{
            		throw ERR_SLIC;
            	}

                assert(klabels.at(ind) >= 0);
                sigmal.at(klabels.at(ind)) += m_lvec[ind];
                sigmaa[klabels[ind]] += m_avec[ind];
                sigmab[klabels[ind]] += m_bvec[ind];
                sigmax[klabels[ind]] += c;
                sigmay[klabels[ind]] += r;
                //------------------------------------
                //edgesum[klabels[ind]] += edgemag[ind];
                //------------------------------------
                clustersize[klabels[ind]] += 1.0;

                ind++;
            }
        }}

        {for( int k = 0; k < numk; k++ )
        {
            if( clustersize.at(k) <= 0 ) clustersize.at(k) = 1;
            inv[k] = 1.0/clustersize.at(k);//computing inverse now to multiply, than divide later
        }}

        {for( int k = 0; k < numk; k++ )
        {
            kseedsl.at(k) = sigmal.at(k)*inv[k];
            kseedsa.at(k) = sigmaa.at(k)*inv[k];
            kseedsb.at(k) = sigmab.at(k)*inv[k];
            kseedsx.at(k) = sigmax.at(k)*inv[k];
            kseedsy.at(k) = sigmay.at(k)*inv[k];
            //------------------------------------
            //edgesum[k] *= inv[k];
            //------------------------------------
        }}

    }
    //print_klabels("After Loop: ", klabels, sz);

}


//===========================================================================
///	EnforceLabelConnectivity
///
///		1. finding an adjacent label for each new component at the start
///		2. if a certain component is too small, assigning the previously found
///		    adjacent label to this component, and not incrementing the label.
//===========================================================================
void SLIC::EnforceLabelConnectivity(
        const vector<int>			labels,//input labels that need to be corrected to remove stray labels
        const int					width,
        const int					height,
        int*&						nlabels,//new labels
        int&						numlabels,//the number of labels changes in the end if segments are removed
        const int&					K) //the number of superpixels desired by the user
{
    //	const int dx8[8] = {-1, -1,  0,  1, 1, 1, 0, -1};
    //	const int dy8[8] = { 0, -1, -1, -1, 0, 1, 1,  1};

    const int dx4[4] = {-1,  0,  1,  0};
    const int dy4[4] = { 0, -1,  0,  1};

    const int sz = width*height;
    const int SUPSZ = sz/K;
    //nlabels.resize(sz, -1);
    for( int i = 0; i < sz; i++ ) nlabels[i] = -1;
    int label(0);
    int* xvec = new int[sz];
    int* yvec = new int[sz];
    int oindex(0);
    int adjlabel(0);//adjacent label
    for( int j = 0; j < height; j++ )
    {
        for( int k = 0; k < width; k++ )
        {
            if( 0 > nlabels[oindex] )
            {
                nlabels[oindex] = label;
                //--------------------
                // Start a new segment
                //--------------------
                xvec[0] = k;
                yvec[0] = j;
                //-------------------------------------------------------
                // Quickly find an adjacent label for use later if needed
                //-------------------------------------------------------
                {for( int n = 0; n < 4; n++ )
                {
                    int x = xvec[0] + dx4[n];
                    int y = yvec[0] + dy4[n];
                    if( (x >= 0 && x < width) && (y >= 0 && y < height) )
                    {
                        int nindex = y*width + x;
                        if(nlabels[nindex] >= 0) adjlabel = nlabels[nindex];
                    }
                }}

                int count(1);
                for( int c = 0; c < count; c++ )
                {
                    for( int n = 0; n < 4; n++ )
                    {
                        int x = xvec[c] + dx4[n];
                        int y = yvec[c] + dy4[n];

                        if( (x >= 0 && x < width) && (y >= 0 && y < height) )
                        {
                            int nindex = y*width + x;

                            if( 0 > nlabels[nindex] && labels[oindex] == labels[nindex] )
                            {
                                xvec[count] = x;
                                yvec[count] = y;
                                nlabels[nindex] = label;
                                count++;
                            }
                        }

                    }
                }
                //-------------------------------------------------------
                // If segment size is less then a limit, assign an
                // adjacent label found before, and decrement label count.
                //-------------------------------------------------------
                if(count <= SUPSZ >> 2)
                {
                    for( int c = 0; c < count; c++ )
                    {
                        int ind = yvec[c]*width+xvec[c];
                        nlabels[ind] = adjlabel;
                    }
                    label--;
                }
                label++;
            }
            oindex++;
        }
    }
    numlabels = label;

    if(xvec) delete [] xvec;
    if(yvec) delete [] yvec;
}



void SLIC::DoSuperpixelSegmentation_ForGivenSuperpixelSize(
        const unsigned int*         ubuff,
        const int					width,
        const int					height,
        vector<int>&				klabels,
        int&						numlabels,
        const int&					superpixelsize,
        const double&               compactness)
{
    //------------------------------------------------
    const int STEP = sqrt(double(superpixelsize))+0.5;
    //------------------------------------------------
    vector<double> kseedsl(0);
    vector<double> kseedsa(0);
    vector<double> kseedsb(0);
    vector<double> kseedsx(0);
    vector<double> kseedsy(0);

    //--------------------------------------------------
    m_width  = width;
    m_height = height;
    int sz = m_width*m_height;
    //klabels.resize( sz, -1 );
    //--------------------------------------------------
    klabels.resize(sz, -1);
    //for( int s = 0; s < sz; s++ ) klabels.at(s) = -1;       // CHANGED klabels[s] = -1 TO klabels[s] = 0
    //--------------------------------------------------
    if(1)//LAB, the default option
    {
        DoRGBtoLABConversion(ubuff, m_lvec, m_avec, m_bvec);
    }
    else//RGB
    {
        m_lvec = new double[sz]; m_avec = new double[sz]; m_bvec = new double[sz];
        for( int i = 0; i < sz; i++ )
        {
            m_lvec[i] = ubuff[i] >> 16 & 0xff;
            m_avec[i] = ubuff[i] >>  8 & 0xff;
            m_bvec[i] = ubuff[i]       & 0xff;
        }
    }
    //--------------------------------------------------
    bool perturbseeds(false);//perturb seeds is not absolutely necessary, one can set this flag to false
    vector<double> edgemag(0);
    if(perturbseeds) DetectLabEdges(m_lvec, m_avec, m_bvec, m_width, m_height, edgemag);
    GetLABXYSeeds_ForGivenStepSize(kseedsl, kseedsa, kseedsb, kseedsx, kseedsy, STEP, perturbseeds, edgemag);


    try
    {
    	PerformSuperpixelSLIC(kseedsl, kseedsa, kseedsb, kseedsx, kseedsy, klabels, STEP, compactness);
    }
    catch(...)
    {
    	throw ERR_SLIC;
    }



    numlabels = kseedsl.size();

    int* nlabels = new int[sz];

    EnforceLabelConnectivity(klabels, m_width, m_height, nlabels, numlabels, double(sz)/double(STEP*STEP));

    {for(int i = 0; i < sz; i++ ) klabels.at(i) = nlabels[i];}

    if(nlabels) delete [] nlabels;

}


void SLIC::DoSuperpixelSegmentation_ForGivenNumberOfSuperpixels(
        const unsigned int*                             ubuff,
        const int					width,
        const int					height,
        vector<int>&				klabels,
        int&						numlabels,
        const int&					K,//required number of superpixels
        const double&                                   compactness)//weight given to spatial distance
{
    const int superpixelsize = 0.5+double(width*height)/double(K);
    DoSuperpixelSegmentation_ForGivenSuperpixelSize(ubuff,width,height,klabels,numlabels,superpixelsize,compactness);
}




//===========================================================================
/// SaveSuperpixelLabels
///
/// Save labels in raster scan order.
//===========================================================================
void SLIC::SaveSuperpixelLabels(
        const vector<int>&          labels,
        const int&                  width,
        const int&                  height,
        const string&               filename,
        const string&               path)
{

#ifdef WINDOWS
    char fname[256];
    char extn[256];
    _splitpath(filename.c_str(), NULL, NULL, fname, extn);
    string temp = fname;
    string finalpath = path + temp + string(".txt");
#else
    string nameandextension = filename;
    size_t pos = filename.find_last_of("/");
    if(pos != string::npos)//if a slash is found, then take the filename with extension
    {
        nameandextension = filename.substr(pos+1);
    }
    string newname = nameandextension.replace(nameandextension.rfind(".")+1, 3, "txt");//find the position of the dot and replace the 3 characters following it.
//    newname.erase(0, label_filename.rfind('/')+1);

    
    newname = newname.insert(newname.find("."), "_seg_labels");
    string finalpath = path + "/" + newname;
    

    
#endif

    std::ofstream outfile;
    outfile.open(finalpath.c_str());

    for( int i = 0; i < height; i++ )
    {
        for( int j = 0; j < width; j++ ) {
            outfile << labels[width*i + j] << ' ';
        }
        outfile << endl;
    }

    outfile.close();
}


