<GameProjectFile>
  <PropertyGroup Type="Node" Name="candy_eye_cap" ID="7b479046-236e-460f-b411-d00aff00b374" Version="2.3.2.3" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="15" Speed="1.0000">
        <Timeline ActionTag="6" FrameType="PositionFrame" Property="Position">
          <PointFrame FrameIndex="0" X="13.0000" Y="0.0000" />
          <PointFrame FrameIndex="5" X="15.0000" Y="0.0000" />
          <PointFrame FrameIndex="10" X="-5.0000" Y="0.0000" />
          <PointFrame FrameIndex="15" X="5.0000" Y="0.0000" />
        </Timeline>
        <Timeline ActionTag="6" FrameType="ScaleFrame" Property="Scale">
          <PointFrame FrameIndex="0" X="1.0000" Y="1.0000" />
          <PointFrame FrameIndex="5" X="1.0000" Y="1.0000" />
          <PointFrame FrameIndex="10" X="1.0000" Y="1.0000" />
          <PointFrame FrameIndex="15" X="1.0000" Y="1.0000" />
        </Timeline>
        <Timeline ActionTag="6" FrameType="RotationSkewFrame" Property="RotationSkew">
          <PointFrame FrameIndex="0" X="0.0000" Y="0.0000" />
          <PointFrame FrameIndex="5" X="0.0000" Y="0.0000" />
          <PointFrame FrameIndex="10" X="0.0000" Y="0.0000" />
          <PointFrame FrameIndex="15" X="0.0000" Y="0.0000" />
        </Timeline>
        <Timeline ActionTag="7" FrameType="PositionFrame" Property="Position">
          <PointFrame FrameIndex="0" X="13.0000" Y="0.0000" />
          <PointFrame FrameIndex="5" X="15.0000" Y="0.0000" />
          <PointFrame FrameIndex="10" X="-5.0000" Y="0.0000" />
          <PointFrame FrameIndex="15" X="5.0000" Y="0.0000" />
        </Timeline>
        <Timeline ActionTag="7" FrameType="ColorFrame" Property="CColor">
          <ColorFrame FrameIndex="0" Alpha="255">
            <Color A="255" R="0" G="0" B="0" />
          </ColorFrame>
          <ColorFrame FrameIndex="5" Alpha="255">
            <Color A="255" R="0" G="0" B="0" />
          </ColorFrame>
          <ColorFrame FrameIndex="10" Alpha="255">
            <Color A="255" R="0" G="0" B="0" />
          </ColorFrame>
          <ColorFrame FrameIndex="15" Alpha="255">
            <Color A="255" R="0" G="0" B="0" />
          </ColorFrame>
        </Timeline>
        <Timeline ActionTag="8" FrameType="PositionFrame" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="0.0000" />
          <PointFrame FrameIndex="8" X="10.0000" Y="0.0000" />
          <PointFrame FrameIndex="15" X="0.0000" Y="0.0000" />
        </Timeline>
        <Timeline ActionTag="8" FrameType="ScaleFrame" Property="Scale">
          <PointFrame FrameIndex="15" X="1.0000" Y="1.0000" />
        </Timeline>
        <Timeline ActionTag="8" FrameType="RotationSkewFrame" Property="RotationSkew">
          <PointFrame FrameIndex="15" X="0.0000" Y="0.0000" />
        </Timeline>
        <Timeline ActionTag="7" Property="Alpha">
          <IntFrame FrameIndex="0" Value="255" />
          <IntFrame FrameIndex="5" Value="255" />
          <IntFrame FrameIndex="10" Value="255" />
          <IntFrame FrameIndex="15" Value="255" />
        </Timeline>
      </Animation>
      <ObjectData Name="Node" CanEdit="False" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="candy" ActionTag="6" Tag="4" IconVisible="False" ObjectIndex="1" ctype="SpriteObjectData">
            <Size X="120.0000" Y="120.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="14.6000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="pic/candy/candy_eye_mh.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="bq" ActionTag="7" Tag="5" IconVisible="False" ObjectIndex="2" ctype="SpriteObjectData">
            <Size X="120.0000" Y="120.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="14.6000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="0" G="0" B="0" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="pic/public/candy_bq07.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="candy_tm" ActionTag="8" Tag="6" IconVisible="False" ObjectIndex="3" ctype="SpriteObjectData">
            <Size X="150.0000" Y="150.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="5.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="pic/candy/candy_tm.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>