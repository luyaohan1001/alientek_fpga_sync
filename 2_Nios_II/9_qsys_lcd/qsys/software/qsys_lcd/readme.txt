˵��
������ʵ�ֽ�Quartus ii���������sof�ļ���NIOS II EDS���������elf�ļ��ϲ�Ϊjic�ļ����Է�����д��
���ݲ��ԣ�������ʹ����Ҫ�߱�����������
1��quartus ii����汾��13.1������
2��Ĭ��quartus ii�������ɵ�sof�ļ����Ŀ¼Ϊ��Ŀ¼�µ�par/output_files�ļ����¡�������ǣ���Ҫ�û������޸Ľű���cof�ļ�
3��nios ii���������·��Ϊquartus ���̸�Ŀ¼�µ�qsys/software�ļ�����

ע��
���������EP4CE10��EPCS16��д�����Ϊ������������Ҫ�û��޸ģ����±����ɴ򿪣�generate_jic.cof�ļ�����Ӧλ�á�

//*********************************************************************************
//����jic�ļ�
//*********************************************************************************
ʹ�÷���
1����generate_jic.tcl��generate_jic.sh��generate_jic.cof�ļ�������nios ii��������¡�
2����eclipse��ѡ��Ӧ�ù��̣��Ҽ�->NIOS II->NIOS command shell��
3��NIOS command shell������"./generate_jic.sh"��
��������ɺ󣬻���Quartus II���̸�Ŀ¼������һ��jicconv���ļ��У�ͬʱ��generate_jic.tcl��generate_jic.cof�ļ�����������parĿ¼�¡���

4����quartus ii�е��Tools -> Tcl Scripts��ѡ��generate_jic.tcl�����run��
�����гɹ�������parĿ¼����������hs_combined.jic���ļ���

5����дhs_combined.jic��FPGA�У��԰忨�ϵ������ϵ磬�¹̼��Ϳ��Կ�ʼ�����ˡ�
