void Channel::calc_fftdataNew(QVector<QPointF> &data)
{
    int n=data.size();
    QVector<float> in1(n);
    QVector<float> in2(n);
    fftwf_complex* out1 = new fftwf_complex[n*2];
    fftwf_complex* out2 = new fftwf_complex[n*2];
    fftwf_complex* out  = new fftwf_complex[n*2];
    double finaldata_fz[256];//ȡ��ֵ�������
    double finaldata_ywh[256];//��λ�������
    double finaldata_ds[256];//ȡ����������
    double finaldata1[128];
    double finaldata2[128];
    QPointF channel;

    fftwf_plan p1,p2;

    for(int i=0;i<n;i++)
    {
        in1[i]=data[i].rx();
        in2[i]=data[i].ry();
    }
    //FFTW_FORWARD�����任 ��FFTW_BACKWARD����任,in���������飬out���������
    p1=fftwf_plan_dft_r2c_1d(n,in1.data(),out1,FFTW_FORWARD);
    p2=fftwf_plan_dft_r2c_1d(n,in2.data(),out2,FFTW_FORWARD);
    fftwf_execute(p1);
    fftwf_execute(p2);
    for(int i=0;i<n;i++)//��Ϊһ����������
    {
        if(i>128)
        {
            out[i][0]=out1[n-i][0]+out2[n-i][1];
            out[i][1]=out2[n-i][0]-out1[n-i][1];
        }
        else
        {
            out[i][0]=out1[i][0]-out2[i][1];
            out[i][1]=out1[i][1]+out2[i][0];
        }
    }

    for(int i=0;i<n;i++)
    {
        finaldata_fz[i]=(out[i][0]*out[i][0]+out[i][1]*out[i][1])/64/64;
    }
    fftwf_destroy_plan(p1);
    fftwf_destroy_plan(p2);
    fftwf_cleanup();
}