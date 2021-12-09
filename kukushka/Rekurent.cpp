TPosition TPosition::GetNextChild()
{
	TPosition ps = *this;
	ps.MakeMoveMV(ind++);
	ps.Calc_MV();
	return ps;
}

TPosition GetChilds(TPosition p)
{
	if(p.ind<p.mcnt)
	{
		TPosition psch;
		for (int i = 0; i < p.mcnt; i++) {
			psch = GetChilds(p);
		}
	}

}

//---------------

// https://www.youtube.com/watch?v=gNiTLPeBLJc